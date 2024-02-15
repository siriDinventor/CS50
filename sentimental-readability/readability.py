import re
import cs50


def count_letters(text):
    letters = sum(c.isalpha() for c in text)
    print(letters)
    return letters


def count_sentence(text):
    sentences = text.count('?') + text.count('!') + text.count('.')
    print(sentences)
    return sentences


def count_word(text):
    words = re.findall(r'\b[\w\'-]+\b', text)
    print(len(words))
    return len(words)


def main():
    # Get input text from the user
    text = cs50.get_string("Text: ")

    # Count the number of letters, sentences, and words in the text
    letters_count = count_letters(text)
    sentence = count_sentence(text)
    words = count_word(text)

    # Calculate average letters per 100 words (L) and average sentences per 100 words (S)
    L = (100.0 * letters_count) / words
    S = (100.0 * sentence) / words

    # Compute the Coleman-Liau index
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    # Determine and print the grade level
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()

