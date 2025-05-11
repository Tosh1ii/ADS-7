// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstdlib>

Train::Train() : operationsCount(0), fCar(nullptr) {}

void Train::addCar(bool isLightOn) {
  Car* newCar = new Car{isLightOn, nullptr, nullptr};

  if (!fCar) {
    fCar = newCar;
    newCar->nextCar = newCar;
    newCar->prevCar = newCar;
  } else {
    Car* lCar = fCar->prevCar;
    newCar->nextCar = fCar;
    newCar->prevCar = lCar;
    lCar->nextCar = newCar;
    fCar->prevCar = newCar;
    fCar = newCar;
  }
}

int Train::getLength() {
  if (!fCar) return 0;
  if (fCar->nextCar == fCar) return 1;

  operationsCount = 0;
  Car* currentCar = fCar;
  int trainSize = 1;

  if (!currentCar->light) {
    currentCar->light = true;
  }

  currentCar = currentCar->nextCar;
  operationsCount += 2;

  while (!currentCar->light) {
    currentCar = currentCar->nextCar;
    operationsCount += 2;
    trainSize++;
  }

  currentCar->light = false;

  if (!fCar->light) {
    return trainSize;
  }

  while (true) {
    currentCar = fCar;
    trainSize = 1;

    if (!currentCar->light) {
      currentCar->light = true;
    }

    currentCar = currentCar->nextCar;
    operationsCount += 2;

    while (!currentCar->light) {
      currentCar = currentCar->nextCar;
      operationsCount += 2;
      trainSize++;
    }

    currentCar->light = false;

    if (!fCar->light) {
      return trainSize;
    }
  }
}

int Train::getOpCount() {
  return operationsCount;
}

Train::~Train() {
  if (!fCar) return;

  if (fCar->nextCar == fCar) {
    delete fCar;
    fCar = nullptr;
    return;
  }

  Car* current = fCar->nextCar;
  while (current != fCar) {
    Car* tempCar = current;
    current = current->nextCar;
    delete tempCar;
  }

  delete fCar;
  fCar = nullptr;
}
