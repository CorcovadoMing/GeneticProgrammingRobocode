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
fire( ( ( 2.9505 - target.x ) * ( target.distance + -3.27016 ) ) );
	}

	void doMovement() {
if ( target.distance == 2.28465 ) {
    setAhead( 1.01583 );
}
else if ( target.bearing == target.distance ) {
    setAhead( target.bearing );
}
if ( target.x == -2.89316 ) {
    setTurnRightRadians( -8.74445 );
}
if ( target.energy > target.y ) {
    setAhead( -2.97128 );
}
	}
	public void onHitWall(HitWallEvent e) {
setAhead( ( -5.5842 - 2.82025 ) );
reverseDirection( 1.18262 );
setTurnRightRadians( target.speed );
if ( target.y > 9.70098 && target.y < 3.21832 ) {
    setAhead( 3.13962 );
}
if ( target.head == -1.95648 && target.energy != target.bearing ) {
    reverseDirection( 6.20026 );
}
if ( target.bearing < target.distance ) {
    reverseDirection( 8.28349 );
}
else if ( target.energy != 3.54835 && direction < -2.30069 ) {
    setAhead( direction );
}
if ( target.head == 6.52137 ) {
    setAhead( target.head );
}
else if ( target.x > target.head || target.head < target.bearing ) {
    setAhead( target.speed );
}
else if ( direction == target.y || target.y < target.bearing ) {
    reverseDirection( target.x );
}
else {
    reverseDirection( 2.86095 );
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
