#!/usr/bin/env python3
"""Download Google Books Ngram export metadata or 1-gram shards."""

from __future__ import annotations

import argparse
import html.parser
import pathlib
import urllib.parse
import urllib.request


BASE_URL = "https://storage.googleapis.com/books/ngrams/books/20200217"


class ExportIndexParser(html.parser.HTMLParser):
    """Collect shard links from the export index page."""

    def __init__(self) -> None:
        super().__init__()
        self.links: list[str] = []

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        if tag != "a":
            return
        href = dict(attrs).get("href")
        if href and href.endswith(".gz"):
            self.links.append(href)


def download(url: str, dest: pathlib.Path) -> None:
    dest.parent.mkdir(parents=True, exist_ok=True)
    with urllib.request.urlopen(url) as response, dest.open("wb") as out:
        out.write(response.read())


def export_index_url(corpus: str) -> str:
    return f"{BASE_URL}/{corpus}/{corpus}-1-ngrams_exports.html"


def total_counts_url(corpus: str) -> str:
    return f"{BASE_URL}/{corpus}/totalcounts-1"


def parse_index(url: str) -> list[str]:
    with urllib.request.urlopen(url) as response:
        html_text = response.read().decode("utf-8")
    parser = ExportIndexParser()
    parser.feed(html_text)
    return [urllib.parse.urljoin(url, link) for link in parser.links]


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--corpus",
        default="eng-us",
        help="Google Ngram corpus shorthand, e.g. eng-us, eng, eng-fiction",
    )
    parser.add_argument(
        "--output-dir",
        default="data/google-ngram",
        help="Directory to store downloaded files",
    )
    parser.add_argument(
        "--download",
        choices=["metadata", "shards", "all"],
        default="metadata",
        help="What to download",
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=0,
        help="Maximum number of shard files to download; 0 means no limit",
    )
    args = parser.parse_args()

    output_dir = pathlib.Path(args.output_dir) / args.corpus
    index_url = export_index_url(args.corpus)
    counts_url = total_counts_url(args.corpus)

    if args.download in {"metadata", "all"}:
        download(index_url, output_dir / "1-ngrams_exports.html")
        download(counts_url, output_dir / "totalcounts-1")

    if args.download in {"shards", "all"}:
        shard_urls = parse_index(index_url)
        if args.limit > 0:
            shard_urls = shard_urls[: args.limit]
        shard_dir = output_dir / "1-grams"
        for shard_url in shard_urls:
            filename = shard_url.rsplit("/", 1)[-1]
            download(shard_url, shard_dir / filename)


if __name__ == "__main__":
    main()
