/***************************************************************************************
  Brightness
***************************************************************************************/
void readPots(){

  if (DMXSerial.receive())
  {
		currBrightness = DMXSerial.read(DMX_Channel);
		tempProgram = map(DMXSerial.read(DMX_Channel + 1), 0, 255, 0, 51);
		currSpeed = DMXSerial.read(DMX_Channel + 2);

		if (millis() > antiSpam)
		{
			currProgram = tempProgram;
			antiSpam = millis() + 200;
		}
  }

}


int fastfloor(float n) {
  return n > 0 ? (int) n : (int) n - 1;
}
float k_fn(int a) {
  s = (A[0] + A[1] + A[2]) * onesixth;
  float x = u - A[0] + s;
  float y = v - A[1] + s;
  float z = w - A[2] + s;
  float t = 0.6f - x * x - y * y - z * z;
  int h = shuffle(i + A[0], j + A[1], k + A[2]);
  A[a]++;
  if (t < 0) return 0;
  int b5 = h >> 5 & 1;
  int b4 = h >> 4 & 1;
  int b3 = h >> 3 & 1;
  int b2 = h >> 2 & 1;
  int b = h & 3;
  float p = b == 1 ? x : b == 2 ? y : z;
  float q = b == 1 ? y : b == 2 ? z : x;
  float r = b == 1 ? z : b == 2 ? x : y;
  p = b5 == b3 ? -p : p;
  q = b5 == b4 ? -q: q;
  r = b5 != (b4^b3) ? -r : r;
  t *= t;
  return 8 * t * t * (p + (b == 0 ? q + r : b2 == 0 ? q : r));
}
int shuffle(int i, int j, int k) {
  return b(i, j, k, 0) + b(j, k, i, 1) + b(k, i, j, 2) + b(i, j, k, 3) + b(j, k, i, 4) + b(k, i, j, 5) + b(i, j, k, 6) + b(j, k, i, 7);
}
int b(int i, int j, int k, int B) {
  return T[b(i, B) << 2 | b(j, B) << 1 | b(k, B)];
}
int b(int N, int B) {
  return N >> B & 1;
}


void effectFunction()
{
  if (currSpeed > 2)
	{
	  //Load starting fade based on currFadeStep
		int tempStep = currFadeStep;

		for (int i = maxPixels; i > -1; i--)
		{
			// get the current colour
			uint32_t curr_col = strip.getPixelColor(i);

			// do some bitshifting
			red3 = (curr_col >> 16) & 0xFF;
			green3 = (curr_col >> 8) & 0xFF;
			blue3 = curr_col & 0xFF;

			switch(tempStep)
			{
        /* Sine Wave
				case 0:
					//no change
					break;
				case 1:
					fadeEffect(1.5, red3, green3, blue3);
					break;
				case 2:
					fadeEffect(2, red3, green3, blue3);
					break;
				case 3:
					fadeEffect(2.5, red3, green3, blue3);
					break;
				case 4:
					fadeEffect(3, red3, green3, blue3);
					break;
				case 5:
					fadeEffect(3.5, red3, green3, blue3);
					break;
				case 6:
					fadeEffect(4, red3, green3, blue3);
					break;
				case 7:
					fadeEffect(4.5, red3, green3, blue3);
					break;
				case 8:
					fadeEffect(5, red3, green3, blue3);
					break;
				case 9:
					fadeEffect(5.5, red3, green3, blue3);
					break;
				case 10:
					fadeEffect(6, red3, green3, blue3);
					break;
				case 11:
					fadeEffect(5.5, red3, green3, blue3);
					break;
				case 12:
					fadeEffect(5, red3, green3, blue3);
					break;
				case 13:
					fadeEffect(4.5, red3, green3, blue3);
					break;
				case 14:
					fadeEffect(4, red3, green3, blue3);
					break;
				case 15:
					fadeEffect(3.5, red3, green3, blue3);
					break;
				case 16:
					fadeEffect(3, red3, green3, blue3);
					break;
				case 17:
					fadeEffect(2.5, red3, green3, blue3);
					break;
				case 18:
					fadeEffect(2, red3, green3, blue3);
					break;
				case 19:
					fadeEffect(1.5, red3, green3, blue3);
					break;
        */
       
       // Pulse
      	case 0:
					//no change
				  break;
				case 1:
					fadeEffect(1.25, red3, green3, blue3);
					break;
				case 2:
					fadeEffect(1.5, red3, green3, blue3);
					break;
				case 3:
					fadeEffect(1.75, red3, green3, blue3);
					break;
				case 4:
					fadeEffect(2, red3, green3, blue3);
					break;
				case 5:
					fadeEffect(2.25, red3, green3, blue3);
					break;
				case 6:
					fadeEffect(2.50, red3, green3, blue3);
					break;
				case 7:
					fadeEffect(2.75, red3, green3, blue3);
					break;
				case 8:
					fadeEffect(3, red3, green3, blue3);
					break;
				case 9:
					fadeEffect(3.5, red3, green3, blue3);
					break;
				case 10:
					fadeEffect(4, red3, green3, blue3);
					break;
				case 11:
					fadeEffect(4.5, red3, green3, blue3);
					break;
				case 12:
					fadeEffect(5, red3, green3, blue3);
					break;
				case 13:
					fadeEffect(5.5, red3, green3, blue3);
					break;
				case 14:
					fadeEffect(6, red3, green3, blue3);
					break;
				case 15:
					fadeEffect(6.5, red3, green3, blue3);
					break;
				case 16:
					fadeEffect(8, red3, green3, blue3);
					break;
				case 17:
					fadeEffect(8.5, red3, green3, blue3);
					break;
				case 18:
					fadeEffect(9, red3, green3, blue3);
					break;
				case 19:
					fadeEffect(10, red3, green3, blue3);
					break;
			}

			//incremement tempStep to prepare for next pixel & catch any rollover
			tempStep += 1;
			if (tempStep > 19)
			{
				tempStep = 0;
			}

			// set the color of the pixel
			strip.setPixelColor(i, strip.Color(int(red3), int(green3), int(blue3)));
		}

    if (effectMillis < millis()){
      effectMillis = millis() + 20 + ((255 - currSpeed) * 2);
      //delay(255 - currSpeed);
      //incremement currFadeStep to prepare for next frame & catch any rollover
      currFadeStep += 1;
      if (currFadeStep > 19)
      {
        currFadeStep = 0;
      }
    } 
	} 
}

void fadeEffect(float fadeAmount, int& R, int& G, int& B)
{
  R = R / fadeAmount;
  G = G / fadeAmount;
  B = B / fadeAmount;
}


/***********************************************************
  hsv2rgb
  Function: Calculate RGB values for colors represented
    in Hue, Saturation, and Value (brightness).
***********************************************************/
void hsv2rgb(float H, float S, float V, int& R, int& G, int& B)
{
  int var_i;
  float var_1, var_2, var_3, var_h, var_r, var_g, var_b;
  if ( S == 0 )                       //HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      //H must be < 1
    var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if ( var_i == 0 ) {
    var_r = V     ;
    var_g = var_3 ;
    var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
    var_r = var_2 ;
    var_g = V     ;
    var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
    var_r = var_1 ;
    var_g = V     ;
    var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
    var_r = var_1 ;
    var_g = var_2 ;
    var_b = V     ;
    }
    else if ( var_i == 4 ) {
    var_r = var_3 ;
    var_g = var_1 ;
    var_b = V     ;
    }
    else                   {
    var_r = V     ;
    var_g = var_1 ;
    var_b = var_2 ;
    }

    //RGB results = 0 ÷ 255 (Production)
    R = (var_r) * 255;
    G = (var_g) * 255;
    B = (var_b) * 255;
  }
}

/*****************************************************************************/
// Simplex noise code:
// From an original algorythm by Ken Perlin.
// Returns a value in the range of about [-0.347 .. 0.347]
float SimplexNoise(float x, float y, float z) {
  // Skew input space to relative coordinate in simplex cell
  s = (x + y + z) * onethird;
  i = fastfloor(x+s);
  j = fastfloor(y+s);
  k = fastfloor(z+s);
   
  // Unskew cell origin back to (x, y , z) space
  s = (i + j + k) * onesixth;
  u = x - i + s;
  v = y - j + s;
  w = z - k + s;;
   
  A[0] = A[1] = A[2] = 0;
   
  // For 3D case, the simplex shape is a slightly irregular tetrahedron.
  // Determine which simplex we're in
  int hi = u >= w ? u >= v ? 0 : 1 : v >= w ? 1 : 2;
  int lo = u < w ? u < v ? 0 : 1 : v < w ? 1 : 2;
   
  return k_fn(hi) + k_fn(3 - hi - lo) + k_fn(lo) + k_fn(0);
}


