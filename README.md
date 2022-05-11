# uva131 The Psychic Poker Player

In 5-card draw poker, a player is dealt a hand of five cards (which may be looked at). The player may
then discard between zero and five of his or her cards and have them replaced by the same number of
cards from the top of the deck (which is face down). The object is to maximize the value of the final
hand. The different values of hands in poker are given at the end of this problem.
Normally the player cannot see the cards in the deck and so must use probability to decide which
cards to discard. In this problem, we imagine that the poker player is psychic and knows which cards
are on top of the deck. Write a program which advises the player which cards to discard so as to
maximize the value of the resulting hand.

## Input

Input will consist of a series of lines, each containing the initial five cards in the hand then the first
five cards on top of the deck. Each card is represented as a two-character code. The first character
is the face-value (A=Ace, 2–9, T=10, J=Jack, Q=Queen, K=King) and the second character is the suit
(C=Clubs, D=Diamonds, H=Hearts, S=Spades). Cards will be separated by single spaces. Each input
line will be from a single valid deck, that is there will be no duplicate cards in each hand and deck.

## Output

Each line of input should produce one line of output, consisting of the initial hand, the top five cards
on the deck, and the best value of hand that is possible. Input is terminated by end of file.
Note: Use the sample input and output as a guide.
Note that the order of the cards in the player’s hand is irrelevant, but the order of the cards in the
deck is important because the discarded cards must be replaced from the top of the deck. Also note
that examples of all types of hands appear in the sample output, with the hands shown in decreasing
order of value.
