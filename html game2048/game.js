document.addEventListener("DOMContentLoaded", () => {
    const grid = document.getElementById("grid");
    const gameOverText = document.getElementById("game-over");
    let board = Array.from({ length: 4 }, () => Array(4).fill(0));
    let score = 0;

    function drawBoard() {
        grid.innerHTML = "";
        board.forEach(row => {
            row.forEach(cell => {
                const cellDiv = document.createElement("div");
                cellDiv.className = "cell";
                cellDiv.textContent = cell === 0 ? "" : cell;
                if (cell !== 0) cellDiv.setAttribute("data-value", cell);
                grid.appendChild(cellDiv);
            });
        });
        document.getElementById("score").textContent = `Score: ${score}`;
    }

    function addRandomTile() {
        let emptyCells = [];
        for (let r = 0; r < 4; r++) {
            for (let c = 0; c < 4; c++) {
                if (board[r][c] === 0) emptyCells.push({ r, c });
            }
        }
        if (emptyCells.length > 0) {
            let { r, c } = emptyCells[Math.floor(Math.random() * emptyCells.length)];
            board[r][c] = Math.random() > 0.1 ? 2 : 4;
        }
    }

    function moveLeft() {
        board = board.map(row => {
            let newRow = row.filter(num => num !== 0);
            for (let i = 0; i < newRow.length - 1; i++) {
                if (newRow[i] === newRow[i + 1]) {
                    newRow[i] *= 2;
                    newRow.splice(i + 1, 1);
                    newRow.push(0);
                    score += newRow[i];
                }
            }
            while (newRow.length < 4) newRow.push(0);
            return newRow;
        });
    }

    function moveRight() {
        board = board.map(row => {
            let newRow = row.filter(num => num !== 0);
            for (let i = newRow.length - 1; i > 0; i--) {
                if (newRow[i] === newRow[i - 1]) {
                    newRow[i] *= 2;
                    newRow.splice(i - 1, 1);
                    newRow.unshift(0);
                    score += newRow[i];
                }
            }
            while (newRow.length < 4) newRow.unshift(0);
            return newRow;
        });
    }

    function moveUp() {
        for (let c = 0; c < 4; c++) {
            let column = [];
            for (let r = 0; r < 4; r++) column.push(board[r][c]);
            column = column.filter(num => num !== 0);
            for (let i = 0; i < column.length - 1; i++) {
                if (column[i] === column[i + 1]) {
                    column[i] *= 2;
                    column.splice(i + 1, 1);
                    column.push(0);
                    score += column[i];
                }
            }
            while (column.length < 4) column.push(0);
            for (let r = 0; r < 4; r++) board[r][c] = column[r];
        }
    }

    function moveDown() {
        for (let c = 0; c < 4; c++) {
            let column = [];
            for (let r = 0; r < 4; r++) column.push(board[r][c]);
            column = column.filter(num => num !== 0);
            for (let i = column.length - 1; i > 0; i--) {
                if (column[i] === column[i - 1]) {
                    column[i] *= 2;
                    column.splice(i - 1, 1);
                    column.unshift(0);
                    score += column[i];
                }
            }
            while (column.length < 4) column.unshift(0);
            for (let r = 0; r < 4; r++) board[r][c] = column[r];
        }
    }

    function handleKeyPress(event) {
        let prevBoard = JSON.stringify(board);
        switch (event.key) {
            case "ArrowLeft":
                moveLeft();
                break;
            case "ArrowRight":
                moveRight();
                break;
            case "ArrowUp":
                moveUp();
                break;
            case "ArrowDown":
                moveDown();
                break;
        }
        if (JSON.stringify(board) !== prevBoard) {
            addRandomTile();
            drawBoard();
        }
    }

    document.addEventListener("keydown", handleKeyPress);
    addRandomTile();
    addRandomTile();
    drawBoard();
});
