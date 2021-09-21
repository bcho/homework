class Solution:
    
    # idea:
    #  - only characters appear >= k times can construct the substring
    #  - construct all possible combinations of substring, search for the "biggest" result
    #    - in this problem, the search space is small...
    def longestSubsequenceRepeatedK(self, s: str, k: int) -> str:
        count_of_characters = [0]  *26
        for c in s:
            count_of_characters[ord(c) - ord('a')] += 1
            
        usable_characters = []
        for idx, count_of_char in enumerate(count_of_characters):
            if count_of_char >= k:
                usable_characters.append(chr(idx + ord('a')))
        usable_characters = usable_characters[::-1]
                
        def is_substr(sub: str) -> bool:
            repeated_times = 0
            sub_idx_to_match = 0
            for idx, c in enumerate(s):
                if len(s) - idx < len(sub) * (k - repeated_times - 1):
                    # remaing characters < expected repeat characters, bail        
                    return False
                if c != sub[sub_idx_to_match]:
                    continue
                sub_idx_to_match += 1
                if sub_idx_to_match >= len(sub):
                    sub_idx_to_match = 0
                    repeated_times += 1
                    if repeated_times == k:
                        return True
            return False
        
        best_so_far = ''
        
        def search(sub: str):
            nonlocal best_so_far
            
            if sub != '':
                if not is_substr(sub):
                    return
                # is a substr
                if len(sub) > len(best_so_far):
                    best_so_far = sub
            for c in usable_characters:
                # try expand substring
                search(sub + c)
                
        search('')
        
        return best_so_far