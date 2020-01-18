var canvas;
var speed = 0.25;
var maxSize = 15;
var falloff = 200;
var steps = 13;
var color1;
var color2;

function windowResized() {
	//console.log('resized');
	resizeCanvas(windowWidth, windowHeight);
}

function setup() {
	canvas = createCanvas(windowWidth, windowHeight);
	canvas.position(0,0);
	canvas.style('z-index', '-1');
	
	textAlign(CENTER);
	noStroke();
	
	color1 = color(150);
	color2 = color(200, 200, 200);
}


function draw() {
	background(0);
	
	for (let x = 0; x < width; x+=steps) {
		for (let y = 0; y < height; y+=steps) {
			let mult = 0.1;
			
			// Decrease size the further it's from the mouse.
			let d = dist(mouseX, mouseY, x, y);
			if (d < falloff) {
				mult = map(d, 0, falloff, 1, 0.1);
			}
			
			// Calculate the size.
			let sw = sin((x*y+frameCount)*speed)*maxSize*mult;
			let absSw = abs(sw);
			
			let t;
			
			// Get values based on its size.
			if (sw > 0) {
				fill(color1);
				t = "0";
			} else {
				fill(color2);
				t = "1";
			}
			
			if (absSw > 2) {
				// Display text.
				textSize(absSw);
				text(t, x, y);
			} else {
				// If it's small enough, draw a circle as an optimization.
				ellipse(x, y, absSw, absSw);
			}
		}
	}
}