function windowResized() {
    //console.log('resized');
    resizeCanvas(windowWidth, windowHeight);
}
function setup() 
{   
    canvas = createCanvas(windowWidth, windowHeight);
    canvas.position(0,0);
    canvas.style('z-index', '-1');
	angleMode(DEGREES);
	colorMode(HSB,100);
	rectMode(CENTER);
	createCanvas(windowWidth,windowHeight);
}
var col = 0;
function draw() 
{
	  col++;
    background(0);
    noFill(255);
    circ(width/2,height/2,(dist(mouseX,mouseY,width/2,height/2)*4));
}

function circ(x,y,s)
{
    //stroke(s/8,s/4,s/2);
		translate(x,y);
		rotate(s/10+(col/2)%180);
		stroke(255,30);
    //fill(s/2,s/8,s/4,50);
		fill(0,0,0,5);
    strokeWeight(s/200);
    //ellipse(x,y,s,s);
		ellipse(0,0,s,s);
		resetMatrix();
    if(s>200)
    {
        circ(x+s/4,y,s/2);
        circ(x-s/4,y,s/2);
        circ(x,y+s/4,s/2);
        circ(x,y-s/4,s/2);
    }
}