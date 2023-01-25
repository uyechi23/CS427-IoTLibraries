# library imports
from flask import Flask
import sqlite3

# create the Flask application object
app = Flask(__name__)

# define a "home route" for your web application
@app.route('/home')
def home():
    return "Hello, World!"

# define a "temp" route that takes two parameters:
# a MAC address and a temperature value
# the <angle brackets> are URL parameters that can 
# take different types of data (strings, ints, etc.)
# the function definition needs these as parameters
# to access and use these values. 
# visiting 127.0.0.1:5000/temp/hi/20.0 should now
# display the string, "hi has submitted: 20.0" on
# your browser. Adding (signed=True) allows negative
# float values, in case it is that cold.
@app.route('/temp/<string:mac>/<float(signed=True):temp>')
def temp(mac, temp):
    # create a connection to a database
    con = sqlite3.connect('database.sqlite3')
    cur = con.cursor()
    
    # create a table if it doesn't exist already
    query = """
        CREATE TABLE IF NOT EXISTS temperatureData (
            macaddress TEXT PRIMARY KEY NOT NULL,
            temperature FLOAT NOT NULL
        )
    """
    cur.execute(query)
    
    # check if there is existing data for this MAC address
    query = """SELECT count(*) FROM temperatureData WHERE macaddress = ?"""
    numMatchingRecords = cur.execute(query, (mac,)).fetchone()[0]
    if numMatchingRecords is 0:
        query = """INSERT INTO temperatureData (macaddress, temperature) VALUES (?, ?)"""
    else:
        query = """REPLACE INTO temperatureData (macaddress, temperature) VALUES (?, ?)"""
    cur.execute(query, (mac, temp))
    
    # commit/save changes
    con.commit()
    
    # retrieve all of the temperature data in the database
    query = """SELECT * FROM temperatureData"""
    allData = cur.execute(query).fetchall()
    
    # iteratively separate and store the temperature data
    temperatureData = []
    for row in allData:
        temperatureData.append(row[1])
    
    # calculate the average temperature
    # yes, we could use numpy, but we don't need a whole library for one calculation
    avgTemperature = sum(temperatureData)/len(temperatureData)
    
    # return the result in a formatted string
    return f'{avgTemperature}'



