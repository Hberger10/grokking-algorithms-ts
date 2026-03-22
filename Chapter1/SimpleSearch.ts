function SimpleSearch(arr: number[], target: number): number {
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === target) {
            return i;
        }
    }
    return -1;
}

const arr= [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const targett = 8;
const resultt = SimpleSearch(arr, targett);
console.log(resultt);
console.log("The big O notation is O(n) because in the worst case we have to check all the elements in the array to find the target or determine that it is not present.");