int main() {
    int cell00 = 0 ;
    int cell01 = 1;
    int cell02 = 0;
    int cell10 = 1;
    int cell11 = 1;
    int cell12 = 1;
    int cell20 = 0;
    int cell21 = 1;
    int cell22 = 0;
    int neighbors = 0;

    neighbors = cell00 + cell01 + cell02 + cell10 + cell12 + cell20 + cell21 + cell22;

    int next = 0;
    if (neighbors == 3) {
        next = 1;
    }

    if (neighbors < 2) {
        next = 0;
    }
    
    if (neighbors > 3) {
        next = 0;
    }

    if (neighbors == 2) {
        if (cell11 == 1) {
            next = 1;
        }
    }

    return next;
}