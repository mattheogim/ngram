# Google Books Ngram

This directory is reserved for official Google Books Ngram downloads.

Recommended first step:

```bash
python3 scripts/google_ngram_fetch.py --corpus eng-us --download metadata
```

That fetches:

- `1-ngrams_exports.html`
- `totalcounts-1`

To download actual 1-gram shard files later:

```bash
python3 scripts/google_ngram_fetch.py --corpus eng-us --download shards --limit 2
```

Use `--limit 0` to fetch every shard for the selected corpus.
