# coding: utf-8

import sys
import json
from collections import Counter


def prepare_tweets(src):
    is_tweet = lambda x: 'text' in x

    lines = [json.loads(line) for line in src.readlines()]
    return list(filter(is_tweet, lines))


def main():
    tweet_file = open(sys.argv[1])
    tweets = prepare_tweets(tweet_file)

    concated_text = ' '.join(i['text'] for i in tweets)
    words = concated_text.split()
    total_count = float(len(words))
    word_count = Counter(words)

    for word, count in word_count.items():
        print word, count / total_count


if __name__ == '__main__':
    main()
