/***************************************************************************************
  COLOR Functions strip.Color(GREEN, RED, BLUE);
***************************************************************************************/

/***************************************************************************************
  Single Colors
***************************************************************************************/
void Green(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,currBrightness,0));//Green
  }
  effectFunction();    
}
void Red(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness,0,0));//Red  
  }
  effectFunction();
}
void Blue(){ 
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,currBrightness));//Blue 
  }
  effectFunction();
}
void White(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/2,currBrightness/3)); //White  
  }
  effectFunction();
}
void Amber(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/10,0)); //Amber 
  }
  effectFunction();
}

void Amber2(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/7, 0)); //Amber 
  }
  effectFunction();
}

void Amber3(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/5, 0)); //Amber  
  }
  effectFunction();
}

void Amber4(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
     strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/4, currBrightness/25)); //Amber  
  }
  effectFunction();
}

void Amber5(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/3, currBrightness/10)); //Amber 
  }
  effectFunction();
}
void WarmWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/2,currBrightness/7)); //White  
  }
  effectFunction();
}
void NeutralWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/2,currBrightness/5)); //White  
  }
  effectFunction();
}
void Teal(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,currBrightness/2,currBrightness/2));//Green & Blue
  }
  effectFunction();  
}

void Purple(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness/2,0,currBrightness/2));//Red & Blue
  }  
  effectFunction();
}

/***************************************************************************************
  Rainbow Colors 
  1) spaceinc = space between colors, increment to have a greater gap
  2) timeinc = time between each color, increment for faster color transitions
***************************************************************************************/
void RainbowOneYoffset(){
  spaceinc = 0.03;
  timeinc = (0.000025 * currSpeed);
  yoffset += timeinc; 
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowTwoYoffset(){
  spaceinc = 0.07;
  timeinc = (0.000025 * currSpeed);
  yoffset += timeinc; ; 
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowThreeXoffset(){
  spaceinc = 0.07;
  timeinc = (0.000025 * currSpeed);
  //yoffset += timeinc; 
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowFourXoffset(){
  spaceinc = 0.03;
  timeinc = (0.000025 * currSpeed);
  //yoffset += timeinc; 
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowBigXoffset(){
  spaceinc = 0.12;
  timeinc = (0.000025 * currSpeed);
  //yoffset += timeinc; 
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowBigYoffset(){
  spaceinc = 0.12;
  timeinc = (0.000025 * currSpeed);
  yoffset += timeinc; ; 
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowMovingPiece(){
  if (currMillis < millis())
  {
    if (currSpeed > 2){
      currStep += 1;
      if (currStep > 19){
        currStep = 0;
      }
      for (int i = maxPixels; i > -1; i--){
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);
        strip.setPixelColor(i+1, strip.Color(red, green, blue));
      }
    }
    float hTemp = h;

    hTemp = h + .5; //space between colors
    
    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }

    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);
    fadeEffect(2, red, green, blue);
    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red2, green2, blue2);
    switch(currStep){
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
        strip.setPixelColor(0, strip.Color(red, green, blue));
        break;
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
        strip.setPixelColor(0, strip.Color(red2, green2, blue2));
        break;
    }
    currMillis = millis() + 20 + ((255 - currSpeed) * 2);
  }
}

/***************************************************************************************
  TWO Colors
***************************************************************************************/
void RedGreen(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,currBrightness,0));// Green
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness,0,0));// Red
    }
  }     
  effectFunction();
}
void PurpleBlue(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,0,currBrightness));// Blue
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness/2,0,currBrightness/2));// Purple
    }  
  }  
  effectFunction();
}
void BlueWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness/2,currBrightness/2,currBrightness/2));// White
    } else {
      strip.setPixelColor(i, strip.Color(0,0,currBrightness));// Blue
    }
  }
  effectFunction();
}
void AmberWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness/2,currBrightness/2,currBrightness/2));// White
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/3,0)); //Amber
    } 
  }
  effectFunction();
}
void GreenBlue(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,currBrightness,0));// Green
    } else {
      strip.setPixelColor(i, strip.Color(0,0,currBrightness)); //Blue
    } 
  }
  effectFunction();   
}
void BlueAmber(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/3,0)); //Amber
    } else {
      strip.setPixelColor(i, strip.Color(0,0,currBrightness)); //Blue
    } 
  }
  effectFunction();   
}
/***************************************************************************************
  Rainbow Flow Colors
***************************************************************************************/
void RainbowFlow(){
	h = h - (currSpeed * .0001);
	if (h > 1){
		h -= 1;
	}
	if (h < 0){
		h += 1;
	}

	float hTemp = h;
  
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
      strip.setPixelColor(i, strip.Color(red,green,blue));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .05; //decrease to space out the colors

    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }
  }
	
}
void DualColorFlow(){
    h = h + (currSpeed * .0001);//increment to make faster
    if (h > 1){
      h -= 1;
    }
    if (h < 0){
      h += 1;
    }

    float hTemp = h;

    hTemp = h + .5; //space between colors
    
    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }

    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red2, green2, blue2);
  
     for(uint16_t i=0; i<strip.numPixels(); i=i+8) {
      for(uint16_t ii=i; ii<(i+4); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red,green,blue));
      }
      for(uint16_t ii=i+4; ii<(i+8); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red2,green2,blue2));   
      }
    }
     
}

void DualColorFlowFat(){
    h = h + (currSpeed * .0001);//increment to make faster
    if (h > 1){
      h -= 1;
    }
    if (h < 0){
      h += 1;
    }

    float hTemp = h;

    hTemp = h + .5; //space between colors
    
    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }

    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red2, green2, blue2);
  
    for(uint16_t i=0; i<strip.numPixels(); i=i+16) {
      for(uint16_t ii=i; ii<(i+8); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red,green,blue));
      }
      for(uint16_t ii=i+8; ii<(i+16); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red2,green2,blue2));   
      }
    }
     
}

void RainbowHsvSlow(){
  h = h + (currSpeed * .00001); //increment to make faster
  
  if (h > 1){
    h -= 1;
  }
  
  if (h < 0){
    h += 1;
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue));// Red 
  }
  
}
void RainbowHsvFast(){
  h = h + (currSpeed * .00001); //increment to make faster
  
  if (h > 1){
    h -= 1;
  }
  
  if (h < 0){
    h += 1;
  }
  hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));// Red 
  }
   
}

void RainbowHsvTight(){
  h = h + .00001; //increment to make faster
  
  if (h > 1){
    h -= 1;
  }
  
  if (h < 0){
    h += 1;
  }
  float hTemp = h;
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue));

    //slowly increment 'h' by small increments to make color flow
    hTemp += float(currSpeed / 10000.0); //decrease to space out the colors

    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }
  }

}

/***********************************************************
  Simplex Noise Pattern (Rainbow Cloud Generator)
***********************************************************/
void SimplexNoisePatternInterpolated(float spaceinc, float timeinc, float yoffset, float xoffset) {

  // Simplex noise for whole strip of LEDs.
  // (Well, it's simplex noise for set number of LEDs and cubic interpolation between those nodes.)
  
    // Calculate simplex noise for LEDs that are nodes:
    // Store raw values from simplex function (-0.347 to 0.347)
    //float xoffset = 0.0;
  float xoffset_holder =  xoffset;
  
    for (int i=0; i<=LEDs_in_strip; i=i+node_spacing) {
      xoffset += spaceinc;
      LED_array_red[i] = SimplexNoise(xoffset,yoffset,0);
      LED_array_green[i] = SimplexNoise(xoffset,yoffset,1);
      LED_array_blue[i] = SimplexNoise(xoffset,yoffset,2);
    }

  xoffset = xoffset_holder;
  
  // Interpolate values for LEDs between nodes
  for (int i=0; i<LEDs_in_strip; i++) {
    int position_between_nodes = i % node_spacing;
    int last_node, next_node;

    // If at node, skip
    if ( position_between_nodes == 0 ) {
      // At node for simplex noise, do nothing but update which nodes we are between
      last_node = i;
      next_node = last_node + node_spacing;
    }
    // Else between two nodes, so identify those nodes
    else {
      // And interpolate between the values at those nodes for red, green, and blue
      float t = float(position_between_nodes) / float(node_spacing);
      float t_squaredx3 = 3*t*t;
      float t_cubedx2 = 2*t*t*t;
      LED_array_red[i] = LED_array_red[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + LED_array_red[next_node] * ( -t_cubedx2 + t_squaredx3 );
      LED_array_green[i] = LED_array_green[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + LED_array_green[next_node] * ( -t_cubedx2 + t_squaredx3 );
      LED_array_blue[i] = LED_array_blue[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + LED_array_blue[next_node] * ( -t_cubedx2 + t_squaredx3 );
    }
  }
  
  // Convert values from raw noise to scaled r,g,b and feed to strip
  for (int i=0; i<LEDs_in_strip; i++) {
    int r = currBrightness*((LED_array_red[i]*734 + 16)/255);
    int g = currBrightness*((LED_array_green[i]*734 + 16)/255);
    int b = currBrightness*((LED_array_blue[i]*734 + 16)/255);
      
    if ( r>255 ) { r=255; }
    else if ( r<0 ) { r=0; }  // Adds no time at all. Conclusion: constrain() sucks.
  
    if ( g>255 ) { g=255; }
    else if ( g<0 ) { g=0; }
  
    if ( b>255 ) { b=255; }
    else if ( b<0 ) { b=0; }  
    //Convert to 24 bit output for WS2811

    if (upsample == 1)
    {
      strip.setPixelColor(i, strip.Color(r, g , b));
    }

    if (upsample == 2)
    {
      strip.setPixelColor(i*2, strip.Color(r, g , b));
      strip.setPixelColor((i*2)+1, strip.Color(r, g , b));
    }
    if (upsample == 3)
    {
      strip.setPixelColor(i*3, strip.Color(r, g , b));
      strip.setPixelColor((i*3)+1, strip.Color(r, g , b));
      strip.setPixelColor((i*3)+2, strip.Color(r, g , b));
    }
	if (upsample == 4)
    {
      strip.setPixelColor(i*4, strip.Color(r, g , b));
      strip.setPixelColor((i*4)+1, strip.Color(r, g , b));
      strip.setPixelColor((i*4)+2, strip.Color(r, g , b));
	  strip.setPixelColor((i*4)+3, strip.Color(r, g , b));
    }

  }
        
  if (yoffset >= 16000)
  {
    yoffset = -26000;
  }

  if (yoffset <= -26000)
  {
    yoffset = 16000;
  }

  if (xoffset >= 16000)
  {
    xoffset = -16000;
  }

  if (xoffset <= -16000)
  {
    xoffset = 16000;
  }

}

//NEW SHIT

void GlowingAmber(){

  if (currMillis < millis())
  {
    currMillis = millis() + (255 - currSpeed);
    hTemp = random(maxPixels);

    if (currBrightness > 0)
    {
      strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 3, 0));
    }
  }
  for (int i = 0; i < maxPixels; i++)
  {
      red = (strip.getPixelColor(i) >> 16 & 0xff);
      green = ((strip.getPixelColor(i) >> 8) & 0xff);
      blue = (strip.getPixelColor(i) & 0xff);

      if (red >= 1)
      {
          red--;
      }
      if (blue >= 1)
      {
          blue--;
      }

      if (green >= 1)
      {
          green--;
      }

      strip.setPixelColor(i, strip.Color(red, green, blue));
  }

}


void GlowingBlue(){

  if (currMillis < millis())
  {
    currMillis = millis() + (255 - currSpeed);
    hTemp = random(maxPixels);

    if (currBrightness > 0)
    {
      strip.setPixelColor(hTemp, strip.Color(0, currBrightness / 3, currBrightness));
    }
  }
  for (int i = 0; i < maxPixels; i++)
  {
      red = (strip.getPixelColor(i) >> 16 & 0xff);
      green = ((strip.getPixelColor(i) >> 8) & 0xff);
      blue = (strip.getPixelColor(i) & 0xff);

      if (red >= 1)
      {
          red--;
      }
      if (blue >= 1)
      {
          blue--;
      }

      if (green >= 1)
      {
          green--;
      }

      strip.setPixelColor(i, strip.Color(red, green, blue));
  }

}

void sparkleRasta(){
    //find lucky pixel
    if (currMillis < millis())
    {
      currMillis = millis() + (255 - currSpeed);
      hTemp = random(maxPixels);
      tempStep += 1;
      if (tempStep > 9)
      { 
        tempStep = 0;
      }

      if (currBrightness > 0)
      {
        switch(tempStep)
        {
          case 0:
            strip.setPixelColor(hTemp, strip.Color(currBrightness, 0, 0));
            break;
          case 3:
            strip.setPixelColor(hTemp, strip.Color(0, currBrightness, 0));
            break;
          case 6:
            strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 1.5, 0));
            break;
        }
      } 
    }
    
   
    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }

}

void GlowingAmberWhite(){

    if (currMillis < millis())
    {
      currMillis = millis() + (255 - currSpeed);
      hTemp = random(maxPixels);
      tempStep += 1;
      if (tempStep > 4)
      {
        tempStep = 0;
      }

      if (currBrightness > 0)
      {
        switch(tempStep)
        {
          case 0:
            strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 3, 0));
            break;
          case 1:
            strip.setPixelColor(hTemp, strip.Color(currBrightness / 2, currBrightness / 2, currBrightness / 2));
            break;
        }
      } 
    }
    
    //determine which color to turn it
  
    
    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }

}

void PurpleGold(){
    if (currMillis < millis())
    {
      currMillis = millis() + (255 - currSpeed);
      hTemp = random(maxPixels);
      tempStep += 1;
      if (tempStep > 1)
      {
        tempStep = 0;
      }

      if (currBrightness > 0)
      {
        if (tempStep == 0)
        {
          strip.setPixelColor(hTemp, strip.Color(currBrightness / 1.5, 0, currBrightness / 2));
        }else{
          strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 3, 0));
        }
      }
    }
    
    //determine which color to turn it

    
    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
}


void PurpleGreen(){
  if (currMillis < millis())
  {
    currMillis = millis() + (255 - currSpeed);
    hTemp = random(maxPixels);
    tempStep += 1;
    if (tempStep > 1)
    {
      tempStep = 0;
    }

    if (currBrightness > 0)
    {
      if (tempStep == 0)
      {
        strip.setPixelColor(hTemp, strip.Color(currBrightness / 1.5, 0, currBrightness / 1.5));
      }else{
        strip.setPixelColor(hTemp, strip.Color(0, currBrightness, 0));
      }
    }
  }
  
  for (int i = 0; i < maxPixels; i++)
  {
    red = (strip.getPixelColor(i) >> 16 & 0xff);
    green = ((strip.getPixelColor(i) >> 8) & 0xff);
    blue = (strip.getPixelColor(i) & 0xff);

    if (red >= 1)
    {
        red--;
    }
    if (blue >= 1)
    {
        blue--;
    }

    if (green >= 1)
    {
        green--;
    }

    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
}


void SparkleBlueGreen(){
    //find lucky pixel
    if (currMillis < millis())
    {
      currMillis = millis() + (255 - currSpeed);
      hTemp = random(maxPixels);

      if (currBrightness > 0)
      {
        switch(tempStep){
          case 0:
            strip.setPixelColor(hTemp, strip.Color(red, currBrightness, blue));
            break;
          case 1:
            strip.setPixelColor(hTemp, strip.Color(red, green, currBrightness));
            break;
        }
        tempStep += 1;
        if (tempStep > 1)
        {
          tempStep = 0;
        }
      }
    }  
    


    red = (strip.getPixelColor(hTemp) >> 16 & 0xff);
    green = ((strip.getPixelColor(hTemp) >> 8) & 0xff);
    blue = (strip.getPixelColor(hTemp) & 0xff);


    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
}

void colorWipe(){
  if (currMillis < millis())
  {
    if (currSpeed > 2){
      tempStep += 1;
    }
    if (tempStep > maxPixels)
    {
      tempStep = 0;
      hTemp = h;
      h = random(1000) / 1000.0;
    }
    currMillis = millis() + (255 - currSpeed);
  }
  hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);

  for(uint16_t i=0; i<tempStep; i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
  }
    
  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
    
  for(uint16_t i=tempStep; i<maxPixels; i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
  }
}

void colorWipeBounce(){
  if (currMillis < millis())
  {
    if (currSpeed > 2){
      if (tempStepDirection == 1){
        tempStep -= 1;
      }
      if (tempStepDirection == 0){
        tempStep += 1;
      }
    }

    if (tempStep > maxPixels)
    {
      tempStepDirection++;
      if (tempStepDirection > 2){
        tempStepDirection = 0;
        h = random(1000) / 1000.0;
        hOld = h;
      }
      h = hOld;
    }
    if (tempStep < 1)
    {
      tempStepDirection++;
      if (tempStepDirection > 1){
        tempStepDirection = 0;
        h = random(1000) / 1000.0;
        hOld = h;
      }
      h = hOld;
    }
    currMillis = millis() + (255 - currSpeed);
  }
  
  hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);

  for(uint16_t i=0; i<tempStep; i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
  }
    
  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
    
  for(uint16_t i=tempStep; i<maxPixels+1; i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
  }
}

void DualColorFlowGreenFast()
{
    float hHigh = .7;
    float hLow = .3;
    float hHigh2 = .85;
    float hLow2 = .6;

    if (h > hHigh)
    {
        h = hHigh;
        fadeDirection = 0;
    }
    if (h < hLow)
    {
        h = hLow;
        fadeDirection = 1;
    }

    if (fadeDirection == 1)
    {
        h += .0001 * (currSpeed / 6); // increment to make faster
    }
    if (fadeDirection == 0)
    {
        h -= .0001 * (currSpeed / 6); // decrement to make faster
    }

    float hTemp = h;

    hTemp = h - .1; // space between colors

    hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness) / 255.0), red2, green2, blue2);

     for(uint16_t i=0; i<strip.numPixels(); i=i+8) {
      for(uint16_t ii=i; ii<(i+4); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red,green,blue));
      }
      for(uint16_t ii=i+4; ii<(i+8); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red2,green2,blue2));   
      }
    }

}

void DualColorFlowFast()
{
    float hHigh = .15;
    float hLow = .05;

    if (h > hHigh)
    {
        h = hHigh;
        fadeDirection = 0;
    }
    if (h < hLow)
    {
        h = hLow;
        fadeDirection = 1;
    }

    if (fadeDirection == 1)
    {
        h += .000005 * currSpeed; // increment to make faster
    }
    if (fadeDirection == 0)
    {
        h -= .000005 * currSpeed; // decrement to make faster
    }

    float hTemp = h;

    hTemp = h - .1; // space between colors

    if (h > 1)
    {
        h -= 1;
    }
    if (h < 0)
    {
        h += 1;
    }

    if (hTemp > 1)
    {
        hTemp -= 1;
    }
    if (hTemp < 0)
    {
        hTemp += 1;
    }
    hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness) / 255.0), red2, green2, blue2);

     for(uint16_t i=0; i<strip.numPixels(); i=i+16) {
      for(uint16_t ii=i; ii<(i+8); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red,green,blue));
      }
      for(uint16_t ii=i+8; ii<(i+16); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red2,green2,blue2));   
      }
    }
}

void DualColorFlowFast2()
{
    float hHigh = .15;
    float hLow = .05;

    if (h > hHigh)
    {
        h = hHigh;
        fadeDirection = 0;
    }
    if (h < hLow)
    {
        h = hLow;
        fadeDirection = 1;
    }

    if (fadeDirection == 1)
    {
        h += .000005 * currSpeed; // increment to make faster
    }
    if (fadeDirection == 0)
    {
        h -= .000005 * currSpeed; // decrement to make faster
    }

    float hTemp = h;

    hTemp = h - .3; // space between colors

    if (h > 1)
    {
        h -= 1;
    }
    if (h < 0)
    {
        h += 1;
    }

    if (hTemp > 1)
    {
        hTemp -= 1;
    }
    if (hTemp < 0)
    {
        hTemp += 1;
    }
    hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness) / 255.0), red2, green2, blue2);

     for(uint16_t i=0; i<strip.numPixels(); i=i+16) {
      for(uint16_t ii=i; ii<(i+8); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red,green,blue));
      }
      for(uint16_t ii=i+8; ii<(i+16); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red2,green2,blue2));   
      }
    }
}

void DualColorFlowFast3()
{
    float hHigh = .15;
    float hLow = .05;

    if (h > hHigh)
    {
        h = hHigh;
        fadeDirection = 0;
    }
    if (h < hLow)
    {
        h = hLow;
        fadeDirection = 1;
    }

    if (fadeDirection == 1)
    {
        h += .000005 * currSpeed; // increment to make faster
    }
    if (fadeDirection == 0)
    {
        h -= .000005 * currSpeed; // decrement to make faster
    }

    float hTemp = h;

    hTemp = h - .7; // space between colors

    if (h > 1)
    {
        h -= 1;
    }
    if (h < 0)
    {
        h += 1;
    }

    if (hTemp > 1)
    {
        hTemp -= 1;
    }
    if (hTemp < 0)
    {
        hTemp += 1;
    }
    hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness) / 255.0), red2, green2, blue2);

     for(uint16_t i=0; i<strip.numPixels(); i=i+16) {
      for(uint16_t ii=i; ii<(i+8); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red,green,blue));
      }
      for(uint16_t ii=i+8; ii<(i+16); ii++)
      {
        strip.setPixelColor(ii, strip.Color(red2,green2,blue2));   
      }
    }
}

void TwinkleRainbow()
{
  if (currMillis < millis())
    {
      currMillis = millis() + (255 - currSpeed);
      hTemp = random(maxPixels);
      h += .0001 * currSpeed;
      if (h > 1)
      {
        h = 0;
      }
      if (h < 0)
      {
        h = 1;
      }
      hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);
      if (currBrightness > 0) {
        strip.setPixelColor(hTemp, strip.Color(red, green, blue));
      }
    }
    
   
    



    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }
        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
}


void rastaFlag()
{
  if (currMillis < millis())
  {
    if (currSpeed > 2){
      currStep += 1;
      if (currStep > 11){
        currStep = 0;
      }
      for (int i = maxPixels; i > -1; i--){
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);
        strip.setPixelColor(i+1, strip.Color(red, green, blue));
      }
    }
    switch(currStep){
      case 0:
      case 1:
      case 2:
      case 3:
        strip.setPixelColor(0, strip.Color(0,currBrightness,0));
        break;
      case 4:
      case 5:
      case 6:
      case 7:
        strip.setPixelColor(0, strip.Color(currBrightness,currBrightness/1.5,0));
        break;
      case 8:
      case 9:
      case 10:
      case 11:
        strip.setPixelColor(0, strip.Color(currBrightness,0,0));
        break;
    }
    currMillis = millis() + 20 + ((255 - currSpeed) * 2);
  }
}


void waterFlow()
{
  if (currMillis < millis())
  {
    if (currSpeed >= 0){
      currStep += 1;
      if (currStep > 11){
        currStep = 0;
      }
      for (int i = maxPixels - 2; i > -1; i--){
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);
        strip.setPixelColor(i+1, strip.Color(red, green, blue));
      }
    }

  switch(currStep){
    case 0:
      hTemp = (random(2700) / 10000.0) + .420;
      if (hTemp > h){
        h += .01;
      } else
      {
        h -= .01;
      }
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
      if (hTemp > h){
        h += .0025;
      } else
      {
        h -= .0025;
      }
      break;
    }

  hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);
  strip.setPixelColor(0, strip.Color(red,green,blue));
  currMillis = millis() + ((100 - currSpeed) * 4);
  }
}

void rainbowFlag()
{
  if ((currMillis < millis()) && (currSpeed>0))
  {
    for (int i = maxPixels; i > -1; i--)
    {
      red = (strip.getPixelColor(i) >> 16 & 0xff);
      green = ((strip.getPixelColor(i) >> 8) & 0xff);
      blue = (strip.getPixelColor(i) & 0xff);
      strip.setPixelColor(i+1, strip.Color(red, green, blue));
    }
     h += .0025; //decrease to space out the colors
    if (h > 1){
      h -= 1;
    }
    if (h < 0){
      h += 1;
    }

    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);
    random(1); //VOOODOOO
    strip.setPixelColor(0, strip.Color(red,green,blue));
    currMillis = millis() + 20 + ((255 - currSpeed) * 2);
  }
  
  
}


void triFlag()
{
  h = h + (currSpeed * .00001); //increment to make faster
  
  if (h > 1){
    h -= 1;
  }
  
  if (h < 0){
    h += 1;
  }

  float hTemp = h;
  
  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);

  //slowly increment 'h' by small increments to make color flow
  hTemp += .166; //decrease to space out the colors
  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }

  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red2, green2, blue2);

  hTemp += .166; 
  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }

  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red3, green3, blue3);

  for(uint16_t i=0; i<strip.numPixels(); i+=9) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
    strip.setPixelColor(i+1, strip.Color(red,green,blue));
    strip.setPixelColor(i+2, strip.Color(red,green,blue));
    strip.setPixelColor(i+3, strip.Color(red3,green3,blue3));
    strip.setPixelColor(i+4, strip.Color(red3,green3,blue3));
    strip.setPixelColor(i+5, strip.Color(red3,green3,blue3));
    strip.setPixelColor(i+6, strip.Color(red2,green2,blue2));
    strip.setPixelColor(i+7, strip.Color(red2,green2,blue2));
    strip.setPixelColor(i+8, strip.Color(red2,green2,blue2));
  }
}

void waterFlag()
{
  if (currMillis < millis())
  {
    if (currSpeed > 2){
      currStep += 1;
      if (currStep > 11){
        currStep = 0;
      }
      for (int i = maxPixels; i > -1; i--){
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);
        strip.setPixelColor(i+1, strip.Color(red, green, blue));
      }
    }
    switch(currStep){
      case 0:
      case 1:
      case 2:
      case 3:
        strip.setPixelColor(0, strip.Color(currBrightness,0,currBrightness / 2));
        break;
      case 4:
      case 5:
      case 6:
      case 7:
        strip.setPixelColor(0, strip.Color(0,currBrightness,0));
        break;
      case 8:
      case 9:
      case 10:
      case 11:
        strip.setPixelColor(0, strip.Color(0,0,currBrightness));
        break;
    }
    currMillis = millis() + 20 + ((255 - currSpeed) * 2);
  }
}
