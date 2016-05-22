import time
import ConfigParser
from dateutil import tz
from datetime import datetime

from flask import Flask
from flask import jsonify
from flask import make_response
from flask import request
from flask.ext.cors import CORS


from domain.mongo import get_points_with_weight

app = Flask(__name__)
CORS(app)


DISPLAY_SPEED = 16  # TODO: get from config


@app.route('/points', methods=["GET"])
def get_drive_points():
    start_ts = request.args.get('start_ts')
    end_ts = request.args.get('end_ts')
    from_speed = request.args.get('from_speed', DISPLAY_SPEED)
    realtime = request.args.get('realtime')
    box = request.args.get('box')


    today_unixtime = None
    if realtime and not start_ts:
        today_day = datetime.utcnow().date()
        today_unixtime = datetime(today_day.year, today_day.month, today_day.day, tzinfo=tz.tzutc()).strftime("%s")

    start_ts = start_ts or today_unixtime

    points = get_points_with_weight(count=10000, from_speed=from_speed, start_ts=start_ts, end_ts=end_ts, box=box)

    response = make_response(jsonify({"points": points}))

    return response


if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=8080)