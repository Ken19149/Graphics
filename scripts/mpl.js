// midpoint line drawing algorithm

function mpl(x0, y0, x1, y1) {
    let xDif = x1 - x0;
    let yDif = y1 - y0;

    let d0 = 2 * yDif - xDif;     // dkCurrent
    let dDif = 2 * (yDif - xDif);

    // ctx.fillRect(x0, y0, 2, 2);
    let currentPoint = [x0, y0];
    let nextPoint = [0, 0];
    // console.log(d0, currentPoint)

    // while (nextPoint[0] != x1 && nextPoint[1] != y1) {
    let n;
    if (Math.abs(x1 - x0) > Math.abs(y1 - y0)) {
        n = Math.abs(x1 - x0);
    } else {
        n = Math.abs(y1 - y0);
    }

    for (let i = 0; i < n; i++) {
        if (d0 < 0) {
            currentPoint = [currentPoint[0] + 1, currentPoint[1]];
            d0 = d0 + 2 * yDif;   // dk+1
            // console.log(d0, currentPoint);
            ctx.fillRect(currentPoint[0], currentPoint[1], 2, 2);
        } else if (d0 >= 0) {
            currentPoint = [currentPoint[0] + 1, currentPoint[1] + 1];
            d0 = d0 + 2 * dDif;
            // console.log(d0, currentPoint);
            ctx.fillRect(currentPoint[0], currentPoint[1], 2, 2);
        }
    }
    // console.log(d0, currentPoint);
}