#!/bin/bash
tests=0
make gen
make brute
make solve
while [ 1 ]; do
  tests=$(($tests+1))  # inkrementacja zmiennej
  echo -n "Test #$tests... "  # echo -n wypisuje bez newline
  echo "$tests $1 $2 $3" | ./gen.e >p.in  # podajemy numer testu i parametry wywołania skryptu do generatora
  ./brute.e <p.in >p1.out
  ./solve.e <p.in >p2.out
  check=`diff -w -q p1.out p2.out`  # diff sprawdza, czy pliki sie roznia;
                                    # opcja -w ignoruje biale znaki; opcja -q wypisuje tylko czy pliki sie roznia
  if [ "$check" != "" ]; then  # czy diff niepusty
    echo "FAILED"
    exit
  fi
  echo -n "OK "
  cat p1.out | head -n 1  # Wypisuje pierwszy (tu akurat jedyny) wiersz wyniku bruta
done