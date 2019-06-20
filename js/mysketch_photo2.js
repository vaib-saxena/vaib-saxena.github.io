const IMAGE_URL = "https://avatars.githubusercontent.com/u/5019072?v=3";
const FRACTION_SIZE = 100;
const ORIGIN_CIRCLE_RADIUS = 3.5;
const PADDING = 50;
var canvas;

let repulsionChangeDistance = 3;
let pointSystem = null;
let targetImage = null;

// ==================================================
// PopCircle クラス
// ==================================================
class PopCircle {
  constructor(originPosition, originRadius, originColor) {
    this.position = originPosition.copy();
    this.origin = originPosition.copy();
    this.velocity = createVector(random(0, 10), random(0, 10));
    this.repulsion = random(1.0, 2.0);
		this.originRepulsion = random(0.01, 0.02);
		this.mouseRepulsion = 0.1;
    this.gravity = 3;
    this.radius = this.originRadius = originRadius;
    this.color = originColor;
  }

  updateState() {
    this._updateStateByMouse();
    this._updateStateByOrigin();
    this.velocity.add(accelerationX, -accelerationY);
    this.velocity.mult(0.9);
    this.position.add(this.velocity);
  }

  _updateStateByMouse() {
    const distanceX = mouseX - this.position.x;
    const distanceY = mouseY - this.position.y;
    const distance = mag(distanceX, distanceY);
    const pointCos = distanceX / distance;
    const pointSin = distanceY / distance;
    
    if (distance < repulsionChangeDistance) {
      this.gravity *= 0.4;
      this.mouseRepulsion = max(0, this.mouseRepulsion * 0.5 - 0.01);
      this.velocity.sub(pointCos * this.repulsion, pointSin * this.repulsion);
      this.velocity.mult(1 - this.mouseRepulsion);
    } else {
      this.gravity += (this.originRepulsion - this.gravity) * 0.1;
      this.mouseRepulsion = min(1, this.mouseRepulsion + 0.03);
    }
  }
  
  _updateStateByOrigin() {
    const distanceX = this.origin.x - this.position.x;
    const distanceY = this.origin.y - this.position.y;
    const distance = mag(distanceX, distanceY);
    
    this.velocity.add(distanceX * this.gravity, distanceY * this.gravity);
    this.radius = this.originRadius + distance / 16;
  }
  
  draw() {
    fill(this.color);
    ellipse(this.position.x, this.position.y, this.radius, this.radius);
  }
}

// ==================================================
// PopCircleSystem クラス
// ==================================================
class PopCircleSystem {
  constructor() {
    this.points = [];

    this._createParticles();
  }
  
  _getPixel(x, y) {
    const pixels = targetImage.pixels;
    const idx = (y * targetImage.width + x) * 4;
    
    if (x > targetImage.width || x < 0 || y > targetImage.height || y < 0) {
      return [0,0,0,0];
    }
    
    return [
    	pixels[idx + 0],
    	pixels[idx + 1],
    	pixels[idx + 2],
    	pixels[idx + 3]
    ];
  }
  
  _createParticles() {
    const iw = targetImage.width;
    const ih = targetImage.height;
    
    for (let i = 0; i < FRACTION_SIZE; i++) {
      for (let j = 0; j < FRACTION_SIZE; j++) {
        const imagePosition = createVector(int(i * iw / FRACTION_SIZE), int(j * ih / FRACTION_SIZE));
        imagePosition.add(round(random(-3, 3)), round(random(-3, 3)));
        
        let originPosition = imagePosition.copy();
        let originRadius = random(ORIGIN_CIRCLE_RADIUS - 3, ORIGIN_CIRCLE_RADIUS + 3);
        let originColor = this._getPixel(imagePosition.x, imagePosition.y);
        
        if (originColor[3] === 0) {
          continue;
        }
        
        originPosition.add(PADDING, PADDING);
        
        let point = new PopCircle(originPosition, originRadius, originColor);
        this.points.push(point);
      }
    }
  }

  updateState() {
    for (let point of this.points) {
      point.updateState();
    }
  }

  draw() {
    for (let point of this.points) {
      point.draw();
    }
  }
}

// ==================================================
// p5の関数
// ==================================================
function preload() {
  targetImage = loadImage(IMAGE_URL);
}

function windowResized() {
	//console.log('resized');
	resizeCanvas(windowWidth, windowHeight);
}

function setup() {
  const canvasWidth = targetImage.width + PADDING * 2;
  const canvasHeight = targetImage.height + PADDING * 2;
	targetImage.loadPixels();
  canvas = createCanvas(windowWidth, windowHeight);
  canvas.position(0,0);
  canvas.style('z-index', '-1');
  noStroke();
  frameRate(70);
  pointSystem = new PopCircleSystem();
}

function draw() {
  background(0);
  
  repulsionChangeDistance = max(0, repulsionChangeDistance - 1.5);
  
  pointSystem.updateState();
  pointSystem.draw();
}

function mouseMoved() {
  repulsionChangeDistance = 30;
}
