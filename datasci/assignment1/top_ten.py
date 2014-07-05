# coding: utf-8


import sys
import json
from collections import Counter


def prepare_tweets(src):
    is_tweet = lambda x: 'text' in x

    lines = [json.loads(line) for line in src.readlines()]
    return list(filter(is_tweet, lines))


def prepare_hashtags(tweets):
    rv = []
    for tweet in tweets:
        for hashtag in tweet['entities']['hashtags']:
            rv.append(hashtag['text'])

    return rv


def main():
    tweet_file = open(sys.argv[1])
    tweets = prepare_tweets(tweet_file)
    hashtags_count = Counter(prepare_hashtags(tweets)).items()

    hashtags_count.sort(key=lambda x: x[1], reverse=True)
    for hashtag, count in hashtags_count[:10]:
        print hashtag, count


if __name__ == '__main__':
    main()
