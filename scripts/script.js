const canvas = document.getElementById('myCanvas');
      const ctx = canvas.getContext('2d');
      canvas.width = 1000;
      canvas.height = 800;
      let startPoint = null;

      canvas.addEventListener('click', (event) => {
        const rect = canvas.getBoundingClientRect();
        const x = event.clientX - rect.left;
        const y = event.clientY - rect.top;

        if (!startPoint) {
          startPoint = { x, y };
          ctx.clearRect(0, 0, canvas.width, canvas.height);
          ctx.fillRect(x - 2, y - 2, 4, 4); // Mark the start point
          } else {
          bsh(startPoint.x, startPoint.y, x, y);
          startPoint = null;
        }
      });

    let hi = [[0,0,1,0],[0,0,0,5],[0,5,1,5],[1,3,1,5],[1,0,1,2],[1,2,2,2],[1,3,2,3],[2,0,2,2],[2,3,2,5],[2,0,3,0],[5,5,4,5],[5,5,5,2],[4,2,5,2],[4,2,4,5],[5,1,4,1],[5,0,5,1],[4,0,4,1],[4,0,5,0],[3,0,3,5],[2,5,3,5]]
    // let hi = [[0,0,0,3]]
    for (i in hi) {
        for (j in hi[i]) {
            hi[i][j] = (hi[i][j]+3)*25
        }
        // dda(hi[i][0], hi[i][1], hi[i][2], hi[i][3]);
    }

    // dda(75+8*25,75+5*25,75+8*25,75+0*25);
    // bsh(75+9*25,75+5*25,75+9*25,75+0*25);
    // mpl(75+10*25,75+0*25,75+10*25,75+10*25);
mpl(10,15,30,40);