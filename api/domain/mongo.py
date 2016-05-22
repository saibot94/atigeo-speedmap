from pymongo import MongoClient

MONGO_HOST = "52.53.195.124"
DB = "hacktm"

client = MongoClient(host=MONGO_HOST)
db = client.get_database(DB)

DISPLAY_SPEED = 16  # TODO: get from config


def get_points(count=None):
    points_cursor = db.drives.find({"speed": {"$gte": DISPLAY_SPEED}},
                                   {'latitude': 1, 'longitude': 1, 'speedkmh': 1, 'unixtime':1, '_id': 0})
    return points_cursor if not count else points_cursor.limit(count)


def new_point(point):
    speed = point['speedkmh']
    if 40 < speed < 50:
        display = speed / 1.2456
    elif  50 < speed < 60:
        display = speed 
    else: 
       display = speed * 1.22

    new_point = {}
    for k, v in point.iteritems():
        if k == 'speed': 
            new_point['weight'] = display
        else:
            new_point[k] = v

    return new_point


def get_points_with_weight(count=None):
    points = get_points(count=count)
    points_with_weight = [new_point(point) for point in points]
    return points_with_weight
