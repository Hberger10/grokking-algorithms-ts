function simpleSearch(ar: number[], target: number): number {
    let quantity=1;
    let left = 0;
    let right = ar.length - 1;
    let middle = Math.floor((left + right) / 2);
    let kick = ar[middle];
    console.log("number kick is " + kick);

        while (kick !== target && left <= right) {
        if (kick > target) {

            
            right = middle - 1;
            console.log("left is " + left);
            console.log("kick " + kick);
            
        } else {
            left = middle + 1;
            console.log("right is " + right + " and kick is " + kick);
            
        }
        quantity++;
        middle = Math.floor((left + right) / 2);
        kick = ar[middle]; 
        
        
        
    }
    return quantity;
}

const ar = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const target = 3;
const result = simpleSearch(ar, target);
console.log(result);
console.log("The big O notation is O(log n) because with each iteration we are halving the search space, leading to a logarithmic number of comparisons relative to the size of the input array.");