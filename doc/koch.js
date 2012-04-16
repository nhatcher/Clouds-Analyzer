
function snowflake(c, iDepth, dRad, n, iWidth, iHeight) {
  var PI = Math.PI;
  var dSide = 2*dRad*Math.cos((n-2)*PI/(2*n));
  var dAngle = (1-(n-2)/n)*PI;
  function leg(iLoop) {
    c.save();
    if (iLoop == 0) {
      c.lineTo(dSide, 0);
    }
    else {
      c.scale(1/3,1/3);
      leg(iLoop-1);
      c.rotate(PI/3);
      leg(iLoop-1);
      c.rotate(-PI*2/3);
      leg(iLoop-1);
      c.rotate(PI/3);
      leg(iLoop-1);
    }
    c.restore();
    c.translate(dSide, 0);
  }
  c.save();
  c.translate(iWidth/2-dSide/2, iHeight/2+dRad*Math.sin((n-2)*PI/(2*n)));
  c.moveTo(0,0);
  leg(iDepth);
  for (var i=0; i<n-1;i++) {
    c.rotate(-dAngle);
    leg(iDepth);
  }
  c.closePath();
  c.restore();
}
