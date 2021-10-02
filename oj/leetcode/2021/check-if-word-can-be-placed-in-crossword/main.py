class Solution:
    def placeWordInCrossword(self, board: List[List[str]], word: str) -> bool:
        
        def match_arr(target_arr: List[str], target_word: str) -> bool:
            if ''.join(target_arr) == target_word:
                return True
            if len(target_word) > len(target_arr):
                return False
            for idx, c in enumerate(target_arr):
                if c == ' ':
                    continue
                if c != target_word[idx]:
                    return False
            return True
        
        def split_arr(arr: List[str]):
            current_chunk = []
            for c in arr:
                if c == '#':
                    if len(current_chunk) == len(word):
                        yield current_chunk
                    current_chunk = []
                    continue
                current_chunk.append(c)
            if len(current_chunk) == len(word):
                yield current_chunk
                
        for row in board:
            for target_arr in split_arr(row):
                print(f'checking by row {target_arr}')
                if match_arr(target_arr, word):
                    return True
            for target_arr in split_arr(row[::-1]):
                print(f'checking by inverse row {target_arr}')
                if match_arr(target_arr, word):
                    return True
            
        for idx in range(len(board[0])):
            row = [board[row][idx] for row in range(len(board))]
            for target_arr in split_arr(row):
                print(f'checking by col {target_arr}')
                if match_arr(target_arr, word):
                    return True
            for target_arr in split_arr(row[::-1]):
                print(f'checking by inverse col {target_arr}')
                if match_arr(target_arr, word):
                    return True
            
        return False