#!/bin/bash
S=$(dirname "$0")
for f in "$@"; do
  python $S/flip.py Matching "$f" || continue
  python configure.py >/dev/null
  python -m ninja >/dev/null 2>&1
  rm -f build/G8MJ01/ok
  if python -m ninja 'build\G8MJ01\ok' 2>&1 | grep -q "32 files OK"; then
    echo "KEEP $f"
  else
    echo "REVERT $f"
    python $S/flip.py NonMatching "$f"
  fi
done
python configure.py >/dev/null; python -m ninja >/dev/null 2>&1; rm -f build/G8MJ01/ok; python -m ninja 'build\G8MJ01\ok' 2>&1 | tail -1
