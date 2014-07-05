# coding: utf-8

import sys
import json
from collections import Counter, defaultdict


def avg(seq):
    return sum(seq) / float(len(seq))


def missing_words_from_afinn111(text, afinn111):
    '''Return list of words that missing from afinn111.'''
    return [word for word in text.split() if word not in afinn111]


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


def prepare_tweet(tweet, afinn111):
    return {
        'tweet': tweet,
        'score': calculate_tweet_score(tweet, afinn111),
        'missing_words': missing_words_from_afinn111(tweet['text'], afinn111)
    }


def prepare_missing_terms(prepared_tweets):
    terms = defaultdict(list)
    for t in prepared_tweets:
        for word in t['missing_words']:
            terms[word].append(t['score'])
    return terms


def main():
    sent_file = open(sys.argv[1])
    tweet_file = open(sys.argv[2])

    afinn111 = prepare_afinn111(sent_file)
    tweets = [prepare_tweet(i, afinn111) for i in prepare_tweets(tweet_file)]
    missing_terms = prepare_missing_terms(tweets)

    for term in missing_terms.keys():
        # Use average score as sentiment score for new terms.
        print term, avg(missing_terms[term])


if __name__ == '__main__':
    main()
