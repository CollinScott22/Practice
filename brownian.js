function brownian(canvasId, messageId) {
  var canvas = document.getElementById(canvasId);
  var ctx = canvas.getContext("2d");

  var drawPos = true;
  var seedResolution = 50;
  var clearShade = 0;

  //window

  var width = canvas.width;
  var height = canvas.height;
  var cx = width/2;
  var cy = height/2;
  var clearStyle = "rgba("+clearShade+", "+clearShade+", "+clearShade+", 1)";

  function radius(x,y) {
    return Math.sqrt((x-cx)*(x-cy)+(y-cx)*(y-cy));
  }
  function test(x,y) {
    if (x < 0 || y < 0 || x >= width || y >= height)
      return false;
    var data = ctx.getImageData(x,y,1,1).data;
    return data[0] != clearShade || data[1] != clearShade || data[2] != clearShade;
  }
  var shade = 120;
  function setc(x,y,c) {
    //var imgd = ctx.createImageData(1,1);
    //var pix = imgd.data;
    shade = (shade + 0.02) % 360;
    if (c) {
      ctx.fillStyle = "hsl("+shade+", 100%, 50%)";
    }else {
      ctx.fillStyle = clearStyle;
    }
    ctx.fillRect(x,y,1,1);
  }
  function set(x,y) {
    setc(x,y,true);
  }
  function clear(x,y) {
    setc(x,y,false);
  }
  ctx.fillStyle = clearStyle;
  ctx.fillRect(0,0,width,height);

  var x;
  var y;

  var closeRadius = 1;

  set(cx,cy);

  function newPos() {
    x = Math.floor(Math.random() * (width/seedResolution))*seedResolution;
    y = Math.floor(Math.random() * (height/seedResolution))*seedResolution;
  }
  newPos();

  var animation = window.setInterval(function () {
    if (drawPos) clear(x,y);
    for (var i = 0; i < 10000, i++) {
      var ox = x;
      var oy = y


      switch (Math.floor(Math.random()*4)) {
        case 0: x++; break;
        case 1: x--; break;
        case 2: y++; break;
        case 3: y--; break;
      }
      if (x < 0 || y < 0 || x >= width || y >= height ||
          radius(x,y) > closeRadius+seedResolution+2) {
            var progress = 1000;
            do {
              newPos();
              progress--;
            } while (( test(x-1,y-1) || test(x,y-1) || test(x+1,y-1) ||
          test(x-1, y) || test(x,y) || test(x+1,y) ||
          test(x-1,y+1) || test(x, y+1) || test(x+1,y+1)) && progress > 0);
          if ( progress <= 0) {
            document.getElementById(messageId).appendChild(
              document.createTextNode("Stopped for lack of room."));
              clearInterval(animation);
              break;
          }
        }
        if (test(x,y)) {
          set(ox,oy);
          closeRadius = Math.max(closeRadius, radius(ox,oy));
          newPos();
        }
    }
    if (drawPos) set(x,y);
  }, 1);
}
