package GP;
import robocode.*;
import java.awt.Color;
import java.util.Random;
public class GP extends AdvancedRobot
{
	Enemy target;
	final double PI = Math.PI;
	int direction = 1;
	Random r = new Random();
	double firePower;
	public void run() {
		target = new Enemy();
		target.distance = 100000;
		setColors(Color.black,Color.black,Color.black);
		setAdjustGunForRobotTurn(true);
		setAdjustRadarForGunTurn(true);
		turnRadarRightRadians(2*PI);
		while(true) {
			doMovement();
			doScanner();
			doGun();
			execute();
		}
	}
	void doFire() {
if ( target.energy != target.energy || target.bearing < 5.63196 ) {
    fire( -5.53144 );
}
fire( ( 0.94356 / 3.81132 ) );
if ( target.speed != 7.1674 ) {
    fire( target.distance );
}
else if ( target.bearing < target.energy ) {
    fire( target.head );
}
else if ( target.speed != -4.04249 ) {
    fire( -3.04457 );
}
	}

	void doMovement() {
if ( target.head > target.x && target.distance != 8.44259 ) {
    setTurnRightRadians( target.y );
}
else if ( target.distance < direction || target.bearing < target.energy ) {
    setAhead( direction );
}
if ( target.energy < target.distance && target.x == target.x ) {
    setTurnRightRadians( target.head );
}
if ( target.head > direction || target.y == target.speed ) {
    setAhead( 8.90348 );
}
else if ( target.distance == 2.44139 && target.energy > 1.32097 ) {
    setAhead( target.y );
}
else if ( direction != target.energy || target.bearing == 9.06379 ) {
    setTurnRightRadians( target.speed );
}
else {
    setTurnRightRadians( 3.17421 );
}
	}
	public void onHitWall(HitWallEvent e) {
setAhead( -4.98875 );
setTurnRightRadians( -7.26085 );
if ( direction == direction && target.x == target.bearing ) {
    setTurnRightRadians( 1.07298 );
}
setTurnRightRadians( 9.84428 );
reverseDirection( -5.69278 );
reverseDirection( 2.79089 );
if ( target.x > target.y || target.head > target.energy ) {
    reverseDirection( -8.73003 );
}
if ( target.bearing > 8.55591 && target.bearing != target.head ) {
    setTurnRightRadians( target.head );
}
if ( target.y > -0.215748 ) {
    setAhead( -7.44815 );
}
if ( target.head > 3.93307 && target.bearing != -0.978676 ) {
    setTurnRightRadians( target.bearing );
}
else if ( target.x < -6.58599 || target.x == 2.76328 ) {
    setTurnRightRadians( target.energy );
}
if ( target.speed > target.x && target.x > 6.79894 ) {
    reverseDirection( 8.78293 );
    setAhead( target.y );
    if ( target.head != target.head || target.x > 8.54866 ) {
        setTurnRightRadians( -0.207234 );
    }
}
	}
	public void reverseDirection(double any) {
		direction = direction * -1;
	}

	void doScanner() {
		double radarOffset;
		if (getTime() - target.ctime > 4) {
			radarOffset = 360;
		} else {
			radarOffset = getRadarHeadingRadians() - absbearing(getX(),getY(),target.x,target.y);
		}
		setTurnRadarLeftRadians(NormaliseBearing(radarOffset));
		setTurnGunLeftRadians(NormaliseBearing(radarOffset+90));
	}

	void doGun() {
		long time = getTime() + (int)(target.distance/(20-(3*firePower)));
		double gunOffset = getGunHeadingRadians() - absbearing(getX(),getY(),target.guessX(time),target.guessY(time));
		setTurnGunLeftRadians(NormaliseBearing(gunOffset));
		doFire();
	}

	double NormaliseBearing(double ang) {
		if (ang > PI)
			ang -= 2*PI;
		if (ang < -PI)
			ang += 2*PI;
		return ang;
	}

	double NormaliseHeading(double ang) {
		if (ang > 2*PI)
			ang -= 2*PI;
		if (ang < 0)
			ang += 2*PI;
		return ang;
	}

	public double getrange( double x1,double y1, double x2,double y2 )
	{
		double xo = x2-x1;
		double yo = y2-y1;
		double h = Math.sqrt( xo*xo + yo*yo );
		return h;
	}

	public double absbearing( double x1,double y1, double x2,double y2 )
	{
		double xo = x2-x1;
		double yo = y2-y1;
		double h = getrange( x1,y1, x2,y2 );
		if( xo > 0 && yo > 0 )
		{
			return Math.asin( xo / h );
		}
		if( xo > 0 && yo < 0 )
		{
			return Math.PI - Math.asin( xo / h );
		}
		if( xo < 0 && yo < 0 )
		{
			return Math.PI + Math.asin( -xo / h );
		}
		if( xo < 0 && yo > 0 )
		{
			return 2.0*Math.PI - Math.asin( -xo / h );
		}
		return 0;
	}

	public void onScannedRobot(ScannedRobotEvent e) {
		if ((e.getDistance() < target.distance)||(target.name == e.getName())) {
			double absbearing_rad = (getHeadingRadians()+e.getBearingRadians())%(2*PI);
			target.name = e.getName();
			target.x = getX()+Math.sin(absbearing_rad)*e.getDistance();
			target.y = getY()+Math.cos(absbearing_rad)*e.getDistance();
			target.bearing = e.getBearingRadians();
			target.head = e.getHeadingRadians();
			target.ctime = getTime();
			target.speed = e.getVelocity();
			target.distance = e.getDistance();
			target.energy = e.getEnergy();
		}
	}

	public void onRobotDeath(RobotDeathEvent e) {
		if (e.getName() == target.name)
			target.distance = 10000;
	}
}

class Enemy {
	String name;
	public double energy;
	public double bearing;
	public double head;
	public long ctime;
	public double speed;
	public double x,y;
	public double distance;
	public double guessX(long when)
	{
		long diff = when - ctime;
		return x+Math.sin(head)*speed*diff;
	}
	public double guessY(long when)
	{
		long diff = when - ctime;
		return y+Math.cos(head)*speed*diff;
	}
}
