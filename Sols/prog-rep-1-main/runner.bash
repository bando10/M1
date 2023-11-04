#!/bin/bash

BINARY=./bin/node

#Parsing des arguments de la ligne de commande avec le flag -f
while getopts f: flag; do
  case "${flag}" in
  f) filename=${OPTARG} ;;
  \?)
    echo "usage : ./run_script.bash -f <your_file_path>."
    exit
    ;;
  esac
done

if [ -z "${filename}" ]; then
  echo "usage : ./run_script -f <your_file_path>.";
  exit
fi

#Extraction du nombre de noeud du fichier passé en argument
while read -r line; do
  if [[ $line == "p edge"* ]]; then
    NODE_COUNT=$(echo "${line}" | cut -d ' ' -f3)
    break
  fi
done <"${filename}"

if [ -z "${NODE_COUNT}" ]; then
  echo "Impossible d'extraire le nombre de noeuds maximal à partir du fichier passé en argument."
  exit
fi

#Test si le Makefile a bien été exécuté
if test -f "$BINARY"; then

  #Creation des processus associé
  for pid in $(seq 1 1 "${NODE_COUNT}"); do
    ${BINARY} -f "${filename}" -p "${pid}" &
  done

else

  echo "Merci d'exécuter le makefile avant de lancer ce script."

fi
