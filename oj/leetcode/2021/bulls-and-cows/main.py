class Solution:
    def getHint(self, secret: str, guess: str) -> str:
        nums_a, nums_b = 0, 0

        unmatched_digits_in_secret = {str(i): 0 for i in range(10)}
        for secret_digit, guess_digit in zip(secret, guess):
            if secret_digit == guess_digit:
                nums_a += 1
                continue

            unmatched_digits_in_secret[secret_digit] += 1

        print(unmatched_digits_in_secret)

        for secret_digit, guess_digit in zip(secret, guess):
            if secret_digit == guess_digit:
                # is a bull match
                continue
            if unmatched_digits_in_secret[guess_digit] > 0:
                nums_b += 1
                unmatched_digits_in_secret[guess_digit] -= 1

        rv = f'{nums_a}A{nums_b}B'
        print(rv)

        return rv
