import ConfigParser

from flask import Flask
from flask import jsonify
from flask import make_response

from domain.mongo import get_points


app = Flask(__name__)


app_conf = ConfigParser.ConfigParser()
app_conf.read("atism.ini")


LEGAL_SPEED_LIMIT = app_conf.get("Legal", "speed")


@app.route('/points', methods=["GET"])
def get_drive_points():
    new_points = []
    points = get_points(count=50000)
    for point in points:
        new_point = {'latitude': point['latitude'], 'longitude': point['longitude'], 'weight': point['speedkmh'] / 10}
        new_points.append(new_point)

    return make_response(jsonify({"points": new_points}))

if __name__ == "__main__":
    app.run(debug=True, port=8080)
