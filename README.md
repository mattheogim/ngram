# N-gram Text Generator

A C-based text generator that creates English-like words using bigram (character-level) Markov chains trained on real English word data.

## How It Works

1. **Letter Frequency Analysis** — Counts individual letter frequencies from a dictionary of ~370k English words
2. **Bigram Frequency Analysis** — Builds a 28×28 transition matrix (a–z + beginning/end of word) from the same dataset
3. **Word Generation** — Samples from the bigram probability distribution to generate new words that follow English spelling patterns

## Project Structure

```
scripts/
├── letter_freq.c              # Step 1: Letter frequency counter
├── step02_bigram_freq.c       # Step 2: Bigram frequency analysis
├── step02_bigram_generate.c   # Step 2: Bigram-based word generator
├── step02_generate.c          # Basic unigram generator
├── step02_top_only.c          # Top-frequency-only generator
└── google_ngram_fetch.py      # Google N-gram data fetcher
```

## Build & Run

```bash
# Compile
gcc scripts/step02_bigram_freq.c -o scripts/step02_bigram_freq
gcc scripts/step02_bigram_generate.c -o scripts/step02_bigram_generate

# Run (from project root)
./scripts/step02_bigram_freq
./scripts/step02_bigram_generate
```

## Example Output

Generated words using bigram model:
```
thera, blion, sticke, dede, mant, ...
```
These aren't real English words, but they *look* like they could be — demonstrating that the model has learned English spelling patterns.

## Data

- Word list: [dwyl/english-words](https://github.com/dwyl/english-words) (~370k words)
- N-gram data: [Google Books Ngram Viewer](https://books.google.com/ngrams/)

## Built With

- C (C11)
- Python (for data fetching)
- CMake
