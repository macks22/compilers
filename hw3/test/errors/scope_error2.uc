

class Main {
    x : Int <- 7;
    
    f (x : Int, y: Int, x: Int) : Int { -- duplicate x
       x + y + z		-- unknown z
    };

    main () : Int {
      {
	out_int(x);
        let x: Int, y: Int, x : Int in { -- duplicate x (I disagree)
	   x <- 2; y <- 3;
           f1 (x + y)		-- unknown method
        }
        tel;
        out_int(y)		-- unknown y
      }
    };
}
