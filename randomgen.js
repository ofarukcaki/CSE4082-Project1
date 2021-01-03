const fs = require('fs');

let _moves = {
  '-4': 'Left',
  4: 'Right',
  '-1': 'Up',
  1: 'Down',
  '-5': 'Up_Left',
  5: 'Down_Right',
  '-3': 'Down_Left',
  3: 'Up_Right',
};

const initial = [1, 12, 11, 10, 2, 13, 0, 9, 3, 14, 15, 8, 4, 5, 6, 7];
let blank_index = 6;
let _set = new Set(); // explored list

let state = [...initial];
let index = 6;

_set.add(state.join(''));

printBoard(state);
console.log('----------------------------');

const depth = process.argv[2];

for (let i = 0; i < depth; i++) {
  moveOnce();
  printBoard(state);
  //   console.log(state.join(''));
  //   console.log(_set);
}

console.log(state.join(', '));
fs.writeFileSync('input', state.join(', '));

function swipe(direction) {
  let newState = [...state];
  //   console.log('c ', newState.join(', '));
  newState[index] = state[index + direction];
  newState[index + direction] = 0;
  //   console.log('> ', newState.join(', '));
  //   console.log('i-d: ', state[index - direction]);
  //   console.log('index: ', state[index]);
  return newState;
}

function randomNumber() {
  const numbers = [-1, 1, -3, 3, -4, 4, -5, 5];
  const rand = numbers[Math.floor(Math.random() * numbers.length)];
  return rand;
}

function isMovePossible(number) {
  if (number == -1) {
    // up
    return [0, 4, 8, 12].indexOf(index) == -1 ? true : false;
  } else if (number == 1) {
    // down
    return [3, 7, 11, 15].indexOf(index) == -1 ? true : false;
  } else if (number == -4) {
    // left
    return [0, 1, 2, 3].indexOf(index) == -1 ? true : false;
  } else if (number == 4) {
    // right
    return [12, 13, 14, 15].indexOf(index) == -1 ? true : false;
  } else if (number == -5) {
    // up left
    return [0, 1, 2, 3, 4, 8, 12].indexOf(index) == -1 ? true : false;
  } else if (number == -5) {
    // up right
    return [0, 4, 8, 12, 13, 14, 15].indexOf(index) == -1 ? true : false;
  } else if (number == -5) {
    // down left
    return [0, 1, 2, 3, 7, 11, 15].indexOf(index) == -1 ? true : false;
  } else if (number == -5) {
    // down right
    return [3, 7, 11, 12, 13, 14, 15].indexOf(index) == -1 ? true : false;
  }
}

function returnPossibleMove() {
  let rand = randomNumber(); // generate random number
  while (!isMovePossible(rand)) {
    rand = randomNumber(); // generate new rand number
  }
  // if it's okay play
  return rand;
}

function moveOnce() {
  let direction = returnPossibleMove(state, index);
  let swiped = swipe(direction);
  while (_set.has(swiped.join(''))) {
    // console.log(`Can't add => ${swiped.join('')}`);
    direction = returnPossibleMove(state, index);
    swiped = swipe(direction);
  }
  index = index + direction;
  console.log(`[${direction}] ${_moves[direction]}`);

  // add explored list
  _set.add(swiped.join(''));
  // replace state
  state = swiped;
}

function printBoard(arr) {
  console.log('-------------------------------------');
  console.log(
    `|   ${String(arr[0]).padStart(2)}   |   ${String(arr[4]).padStart(
      2
    )}   |   ${String(arr[8]).padStart(2)}   |   ${String(arr[12]).padStart(
      2
    )}   |`
  );
  console.log(`-------------------------------------`);
  console.log(
    `|   ${String(arr[1]).padStart(2)}   |   ${String(arr[5]).padStart(
      2
    )}   |   ${String(arr[9]).padStart(2)}   |   ${String(arr[13]).padStart(
      2
    )}   |`
  );
  console.log(`-------------------------------------`);
  console.log(
    `|   ${String(arr[2]).padStart(2)}   |   ${String(arr[6]).padStart(
      2
    )}   |   ${String(arr[10]).padStart(2)}   |   ${String(arr[14]).padStart(
      2
    )}   |`
  );
  console.log(`-------------------------------------`);
  console.log(
    `|   ${String(arr[3]).padStart(2)}   |   ${String(arr[7]).padStart(
      2
    )}   |   ${String(arr[11]).padStart(2)}   |   ${String(arr[15]).padStart(
      2
    )}   |`
  );
  console.log(`-------------------------------------`);
}
