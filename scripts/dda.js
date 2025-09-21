// digital differential analyzer

function dda(x1, y1, x2, y2) {
        let xDif = x2 - x1;
        let yDif = y2 - y1;
        let m = yDif/xDif;

        let steps;

        if (Math.abs(xDif) >= Math.abs(yDif)) {
            steps = Math.abs(xDif);
        } else {
            steps = Math.abs(yDif);
        }

        let xInc = xDif/steps;
        let yInc = yDif/steps;

        let currentPoint = [x1,y1]
        ctx.fillRect(x1, y1, 2, 2);
        for (let i=0;i<steps;i++) {
            let nextPoint = [Math.round(currentPoint[0] + xInc), Math.round(currentPoint[1] + yInc)];
            ctx.fillRect(nextPoint[0], nextPoint[1], 2, 2);
            // console.log(nextPoint)
            currentPoint = nextPoint;
        }
    }