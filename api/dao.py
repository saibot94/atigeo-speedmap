import random
from datetime import datetime

from elasticsearch import Elasticsearch
from elasticsearch import helpers
from faker import Factory

ES_ENDPOINT = "search-hacktm2016-atigeo-xsynhcvmgcugkkyuvrpnaxqxbe.us-west-1.es.amazonaws.com"
POINTS_INDEX = "test-points"
POINTS_DOC_TYPE = "points"
PAGE_SIZE = 10  # It actually retrieves 5 * PAGE_SIZE
LEGAT_SPEED_QUERY = {"query": {"range": {"speed": {"gte": 50}}}}

es = Elasticsearch([{'host': ES_ENDPOINT, 'port': 80}])
faker = Factory.create()


def create_bulk_points(count=None):
    cnt = count or 10
    faults = False
    for idx in range(cnt):
        print "Doc: %s" % idx
        doc = {
            'timestamp': datetime.now(),
            'lat': faker.latitude(),
            'long': faker.longitude(),
            'speed': random.choice(range(25, 120))
        }
        res = es.index(index=POINTS_INDEX, doc_type='points', body=doc)
        if not res['created']:
            faults = True

    es.indices.refresh(index=POINTS_INDEX)
    print 'Created %s points. Faults: %s' % (cnt, faults)


def search_points():
    res = es.search(
        index=POINTS_INDEX,
        body={"query": {"range": {"speed": {"gte": 50}}}},
        _source=['lat', 'long', 'speed'],
    )

    hits = res["hits"]
    print "Got %s results" % hits["total"]
    for point in hits["hits"]:
        print point["_source"]


def delete_points_index():
    es.indices.delete(index=POINTS_INDEX)


def get_all_points():
    points = helpers.scan(
        es,
        query={"query": {"range": {"speed": {"gte": 50}}}},
        index=POINTS_INDEX,
        doc_type=POINTS_DOC_TYPE,
        fields=("lat", "long", "speed"),
    )

    points = list(points)
    print points


def search_all_points():
    res = es.search(index=POINTS_INDEX, body={"query": {"range": {"speed": {"gte": 50}}}})
    print res


def _scroll_points(query=None, size=50):
    if not query:
        raise ValueError("The query arg. cannot be empty")

    res = es.search(
        index=POINTS_INDEX,
        body=query,
        search_type="scan",
        size=size / 5,
        scroll="60s",
        _source=["lat"]
    )

    scroll_size = res['hits']['total']
    while scroll_size:
        try:
            scroll_id = res['_scroll_id']
            points_batch = es.scroll(scroll_id=scroll_id, scroll='60s')
            points_data = points_batch['hits']['hits']
            yield points_data, len(points_data)
            scroll_size = len(points_batch['hits']['hits'])
        except:
            break


def main():
    for points_batch, batch_size in _scroll_points(LEGAT_SPEED_QUERY):
        print batch_size, points_batch


if __name__ == "__main__":
    main()
