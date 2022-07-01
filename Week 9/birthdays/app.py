import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
import json

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        if request.form.get("name") and request.form.get("month") and request.form.get("day"):
            if not db.execute("SELECT name, month, day FROM birthdays WHERE name LIKE ? AND month LIKE ? AND day LIKE ?", request.form.get("name"), request.form.get("month"), request.form.get("day")):
                db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?);", request.form.get("name"), request.form.get("month"), request.form.get("day"))
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays;")
        return render_template("index.html", birthdays=birthdays)

@app.route('/ProcessID/<string:id>', methods =['POST'])
def ProcessID(id):
    id=json.loads(id)
    for num in id:
        db.execute("DELETE FROM birthdays WHERE id LIKE ?;", num)
    return redirect("/DeleteSuccess")

@app.route('/DeleteSuccess', methods=["GET", "POST"])
def DeleteSucess():
    birthdays = db.execute("SELECT * FROM birthdays;")
    return render_template("index.html", birthdays=birthdays)
