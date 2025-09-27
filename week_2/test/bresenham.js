function bresenhamLine(x0, y0, x1, y1) {
        let dx = Math.abs(x1 - x0);
        let dy = Math.abs(y1 - y0);
        let sx = (x0 < x1) ? 1 : -1;
        let sy = (y0 < y1) ? 1 : -1;
        let err = dx - dy;

        function draw() {
          ctx.fillRect(x0, y0, 2, 2);
          if ((x0 === x1) && (y0 === y1)) return;
          let e2 = 2 * err;
          if (e2 > -dy) { err -= dy; x0 += sx; }
          if (e2 < dx) { err += dx; y0 += sy; }
          requestAnimationFrame(draw);
        }
        draw();
      }

