class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        f0, f1 = [0] * (len(word2) + 1), [0] * (len(word2) + 1)

        for w2idx in range(1, len(word2) + 1):
            # insert only
            f0[w2idx] = w2idx

        for w1idx in range(1, len(word1) + 1):
            # insert only
            f1[0] = w1idx
            for w2idx in range(1, len(word2) + 1):
                if word1[w1idx - 1] == word2[w2idx - 1]:
                    # no edit required
                    # f[i][j] = f[i - 1][j - 1]
                    f1[w2idx] = f0[w2idx - 1]
                else:
                    f1[w2idx] = min(
                        # replace: f[i][j] = f[i-1][j-1] + 1
                        f0[w2idx - 1],
                        # delete: f[i][j] = f[i-1][j] + 1
                        f0[w2idx],
                        # insert: f[i][j] = f[i][j-1] + 1
                        f1[w2idx - 1]
                    ) + 1
            f0, f1 = f1[:], [0] * (len(word2) + 1)

        return f0[len(word2)]
