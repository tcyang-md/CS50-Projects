import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    cash = int((db.execute("SELECT cash FROM users WHERE id = ?", user_id))[0]['cash'])
    stock_list =[]
    stock_portfolio = []
    grand_total = cash

    for item in db.execute("SELECT DISTINCT stock FROM transactions WHERE user_id = ?", user_id):
        stock_list.append(item['stock'])

    for stock in stock_list:
        shares_bought = db.execute("SELECT SUM(shares) FROM transactions WHERE stock = ? AND buy_sell = ? AND user_id = ?", stock, "buy", user_id)[0]['SUM(shares)']
        shares_sold = db.execute("SELECT SUM(shares) FROM transactions WHERE stock = ? AND buy_sell = ? AND user_id = ?", stock, "sell", user_id)[0]['SUM(shares)']
        if shares_bought is None:
            shares_bought = 0
        elif shares_sold is None:
            shares_sold = 0
        current_shares = shares_bought-shares_sold
        print(current_shares)

        if current_shares != 0:
            tmp_dict = {
                "symbol" : stock,
                "name" : lookup(stock)["name"],
                "shares" : current_shares,
                "current_price" : usd(lookup(stock)["price"]),
                "holding" : usd(lookup(stock)["price"] * current_shares)
            }
            grand_total = grand_total + int(db.execute("SELECT SUM(shares) FROM transactions WHERE stock = ?", stock)[0]['SUM(shares)']) * lookup(stock)["price"]
            stock_portfolio.append(tmp_dict)

    return render_template("index.html", cash=cash, stock_portfolio=stock_portfolio, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Default loading of the buy page
    if request.method == "GET":
        return render_template("buy.html")

    # This is post

    stock = lookup(request.form.get("symbol"))
    # check if ticker returned a stock
    if stock is None:
        return apology("must provide valid ticker symbol", 400)
    symbol = stock["symbol"]
    price = stock["price"]
    # check shares for decimals and for other non-digit values
    if not request.form.get("shares").isdigit():
        return apology("must provide valud number of shares", 400)
    shares = int(request.form.get("shares"))
    user_id = session["user_id"]
    buy_sell = "buy"

    # invalid number of shares
    if shares <= 0:
        return apology("must provide valud number of shares", 400)
    else:
        current_balance = int((db.execute("SELECT cash FROM users WHERE id = ?", user_id))[0]['cash'])
        transaction = shares * price
        new_balance = current_balance - transaction
        # Trying to buy too much stock, not enough money
        if new_balance < 0:
            return apology("Not enough funds", 400)
        # Can afford the stock
        else:
            # record purchase in the database
            db.execute("INSERT INTO transactions (user_id, buy_sell, stock, shares, price, total, date, time) VALUES (?, ?, ?, ?, ?, ?, (SELECT DATE('now')), (SELECT TIME('now')))",
            user_id, buy_sell, symbol, shares, price, transaction)
            # set the new balance
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, user_id)

            return render_template("purchase_complete.html", stock=stock, shares=shares, price=usd(price), transaction=usd(transaction), new_balance=usd(new_balance))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    history = db.execute("SELECT stock, buy_sell, shares, price, total, date, time FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # Default page
    if request.method == "GET":
        return render_template("quote.html")

    # Submitted a ticker/POST
    symbol = request.form.get("symbol")
    stock = lookup(symbol)
    if symbol == "" or not stock:
        return apology("must provide valid ticker symbol", 400)
    return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    pw = request.form.get("password")
    confirm = request.form.get("confirmation")

    # Ensure username was submitted
    if not request.form.get("username"):
        return apology("must provide username", 400)

    # Check if username was taken
    elif db.execute("SELECT * FROM users WHERE username LIKE ?", username):
        return apology("username already taken", 400)

    # Confirm password
    elif pw == "" or confirm == "" or pw != confirm:
        return apology("enter valid password and confirmation", 400)

    # Insert into db and hash password
    else:
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(pw))
        return render_template("congrats.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stock_list = []
    user_id = session["user_id"]
    sell = "sell"
    buy = "buy"

    # get all stocks and put them in array
    for item in db.execute("SELECT DISTINCT stock FROM transactions WHERE user_id = ?", user_id):
        stock_name = item['stock']
        stock_bought = db.execute("SELECT SUM(shares) FROM transactions WHERE stock = ? AND buy_sell=? AND user_id = ?", stock_name, buy, user_id)[0]['SUM(shares)']
        stock_sold = db.execute("SELECT SUM(shares) FROM transactions WHERE stock = ? AND buy_sell=? AND user_id=?", stock_name, sell, user_id)[0]['SUM(shares)']
        # Accounts for just bought, never sold before
        if stock_sold is None:
            stock_sold = 0
        # Adds stock to the drop down menu if there is stock available to sell
        if stock_bought-stock_sold > 0:
            stock_list.append(stock_name)


    # get defaults to showing all stocks, pass stock list
    if request.method == "GET":
        return render_template("sell.html", stock_list=stock_list)

    # post request from the form
    # check if selected a valid stock
    symbol = request.form.get("symbol")
    if symbol not in stock_list:
        return apology("must select a valid stock", 400)
     # check shares for decimals and for other non-digit values
    if not request.form.get("shares").isdigit():
        return apology("must provide valud number of shares", 400)
    shares = int(request.form.get("shares"))


    shares_bought = db.execute("SELECT SUM(shares) FROM transactions WHERE stock = ? AND buy_sell = ?", symbol, buy)[0]['SUM(shares)']
    shares_sold = db.execute("SELECT SUM(shares) FROM transactions WHERE stock = ? AND buy_sell = ?", symbol, sell)[0]['SUM(shares)']
    if not shares_bought:
        shares_bought = 0
    elif not shares_sold:
        shares_sold = 0
    current_shares = shares_bought-shares_sold

    new_shares = current_shares - shares
    price = lookup(symbol)["price"]

    # catches invalid number of shares
    if shares <= 0 or shares > current_shares:
        return apology("Attempt to sell invalid number of shares", 400)

    # change cash
    cash = int((db.execute("SELECT cash FROM users WHERE id = ?", user_id))[0]['cash'])
    transaction = shares * price
    new_balance = cash + transaction


    db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, user_id)

    # add to transactions list
    db.execute("INSERT INTO transactions (user_id, buy_sell, stock, shares, price, total, date, time) VALUES (?, ?, ?, ?, ?, ?, (SELECT DATE('now')), (SELECT TIME('now')))",
        user_id, sell, symbol, shares, price, transaction)

    return render_template("sold.html", name=lookup(symbol)['name'], symbol=symbol, shares=shares, price=usd(price), transaction=usd(transaction), new_balance=usd(new_balance), new_shares=new_shares)

@app.route("/changepw", methods=["GET", "POST"])
@login_required
def changepw():
    """change pw of user"""

    user_id = session["user_id"]
    username = db.execute("SELECT username FROM users WHERE id = ?", user_id)[0]['username']

    if request.method == "GET":
        return render_template("changepw.html", username=username)


    # post
    oldpw = request.form.get("oldpw")
    newpw = request.form.get("newpw")
    confirmnewpw = request.form.get("confirmnewpw")

    # either old password in sql and password they inputted aren't the same, or newpw/confirmnewpw don't match, or either of the fields are empty
    if check_password_hash(oldpw, db.execute("SELECT hash FROM users WHERE id= ?", user_id)) or newpw != confirmnewpw or newpw == "" or confirmnewpw == "":
        return apology("Please re-enter password")

    # Insert into db and hash password because it's valid
    else:
        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(newpw), user_id)
        return render_template("changedpw.html", username=username)