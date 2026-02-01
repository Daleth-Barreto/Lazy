
import sys
import difflib

def main():
    if len(sys.argv) < 3:
        # Default failsafe
        print("NO")
        return

    str1 = sys.argv[1].lower()
    str2 = sys.argv[2].lower()

    # 1. Exact Match (Case Insensitive)
    if str1 == str2:
        print("YES")
        return

    # 2. Difflib Ratio (Gestalt Pattern Matching)
    # Better than raw Levenshtein for identifying "close" strings
    matcher = difflib.SequenceMatcher(None, str1, str2)
    ratio = matcher.ratio()

    # Threshold: 0.75 (Allow ~25% difference)
    # Example: hello vs hallo = 0.8
    # Example: apple vs aple = 0.88
    if ratio >= 0.75:
        print("YES")
        return

    # 3. Future Extension: WordNet Synonyms (NLTK)
    # try:
    #     from nltk.corpus import wordnet
    #     # check synsets...
    # except ImportError:
    #     pass

    print("NO")

if __name__ == "__main__":
    main()
