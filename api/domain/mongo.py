from pymongo import MongoClient

MONGO_HOST = "52.53.195.124"
DB = "hacktm"
COLLECTION_NAME = "demo"

client = MongoClient(host=MONGO_HOST)
db = client.get_database(DB)

FIELDS = {
    'latitude': 1,
    'longitude': 1,
    'unixtime': 1,
    'speedkmh': 1,
    'ingestiontime': 1,
    '_id': 0
}


def get_points(count=None, from_speed=None, start_ts=None, end_ts=None, box=None, realtime=False):
    query_conditions = [{"speed": {"$gte": from_speed}}]
    if box:
        nlat = box['northeastern']['lat']
        elong = box['northeastern']['long']
        slat = box['southwestern']['lat']
        wlong = box['southwestern']['lang']
        query_conditions.append({"and": [{"latitude":  {"$lte": nlat}},
                                         {"latitude":  {"$gte": slat}},
                                         {"longitude": {"$gte": wlong}},
                                         {"longitude": {"$lte": elong}}]})

    if realtime:
        query_conditions.append({"ingestiontime": {"$gte": int(start_ts)}})

    if start_ts and not realtime:
        query_conditions.append({"unixtime": {"$gte": start_ts}})

    if end_ts:
        query_conditions.append({"unixtime": {"$lte": end_ts}})

    if len(query_conditions) == 1:
        query = query_conditions[0]
    else:
        query = {"$and": query_conditions}

    print query
    points_cursor = db.demo.find(query, FIELDS)
    return points_cursor if not count else points_cursor.limit(count)


def new_point(point):
    speed = point['speedkmh']
    if 40 < speed < 50:
        display = speed / 1.2456
    elif 50 < speed < 60:
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


def get_points_with_weight(count=None, from_speed=None, start_ts=None, end_ts=None, box=None, realtime=False):
    points = get_points(count=count, from_speed=from_speed, start_ts=start_ts, end_ts=end_ts, box=box, realtime=realtime)
    points_with_weight = [new_point(point) for point in points]
    return points_with_weight
