import time
import ConfigParser
from dateutil import tz
from datetime import datetime

from flask import Flask
from flask import jsonify
from flask import make_response
from flask import request
from flask.ext.cors import CORS


from domain.mongo import get_points_with_weight, get_speed_stats, get_dangerous_streets

app = Flask(__name__)
CORS(app)


DISPLAY_SPEED = 16  # TODO: get from config
COUNT = 10000


@app.route('/points', methods=["GET"])
def get_drive_points():
    start_ts = request.args.get('start_ts')
    end_ts = request.args.get('end_ts')
    from_speed = request.args.get('from_speed', DISPLAY_SPEED)
    box = request.args.get('box')
    collection = request.args.get('collection', 'demo')

    points = get_points_with_weight(collection=collection, count=COUNT, from_speed=from_speed, start_ts=start_ts, end_ts=end_ts, box=box)

    response = make_response(jsonify({"points": points}))

    return response


@app.route('/realtime-points', methods=["GET"])
def get_relatime_drive_points():
    start_ts = request.args.get('start_ts')
    from_speed = request.args.get('from_speed', DISPLAY_SPEED)
    box = request.args.get('box')
    collection = request.args.get('collection', 'realtime')

    if not start_ts:
        today_day = datetime.utcnow().date()
        today_unixtime = datetime(today_day.year, today_day.month, today_day.day, tzinfo=tz.tzutc()).strftime("%s")
        start_ts = today_unixtime

    points = get_points_with_weight(collection=collection, count=COUNT, from_speed=from_speed, start_ts=start_ts, box=box, realtime=True)

    response = make_response(jsonify({"points": points}))

    return response


@app.route('/stats/speed', methods=["GET"])
def get_stats_speed():
    collection = request.args.get('collection', 'demo')
    stats = get_speed_stats(collection)
    return make_response(jsonify(stats))


@app.route('/stats/dangerous-streets', methods=["GET"])
def get_stats_dangerous_streets():
    collection = request.args.get('collection', 'demo')
    stats = get_dangerous_streets(collection)
    return make_response(jsonify({"dangerous": stats}))


if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=8080)