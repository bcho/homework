# coding: utf-8

import sys
import json
from collections import Counter


def prepare_afinn111(src):
    rv = {}
    for line in src.readlines():
        term, score = line.strip().split('\t')
        rv[term] = int(score)
    return rv


def prepare_tweets(src):
    is_tweet = lambda x: 'text' in x

    lines = [json.loads(line) for line in src.readlines()]
    return list(filter(is_tweet, lines))


def calculate_tweet_score(tweet, afinn111):
    word_count = Counter(tweet['text'].split())

    score = 0
    for word, count in word_count.items():
        score += afinn111.get(word, 0) * count

    return score


def main():
    sent_file = open(sys.argv[1])
    tweet_file = open(sys.argv[2])

    afinn111 = prepare_afinn111(sent_file)
    tweets = prepare_tweets(tweet_file)

    for tweet in tweets:
        print calculate_tweet_score(tweet, afinn111)


if __name__ == '__main__':
    main()
