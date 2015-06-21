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
if ( target.head < -7.47476 || target.y > target.y ) {
    fire( -5.35666 );
}
else if ( target.x != target.speed && target.x < 9.67832 ) {
    fire( target.head );
}
fire( 5.53545 );
if ( target.head < -7.47476 || target.y > target.y ) {
    fire( -5.35666 );
}
else if ( target.x != target.speed && target.x < 9.67832 ) {
    fire( target.head );
}
	}

	void doMovement() {
setAhead( target.y );
setTurnRightRadians( ( -9.53145 + target.head ) );
if ( target.distance > 5.72269 || target.bearing > -0.130382 ) {
    setAhead( direction );
}
if ( target.bearing > direction || target.energy > target.x ) {
    setTurnRightRadians( target.energy );
}
setAhead( direction );
if ( target.energy != direction || target.x == target.head ) {
    setTurnRightRadians( 8.88129 );
}
if ( target.distance == -4.7309 ) {
    setTurnRightRadians( direction );
}
if ( target.bearing > direction || target.energy > target.x ) {
    setTurnRightRadians( 8.88129 );
}
else if ( direction == -8.20343 || target.y != 6.45069 ) {
    setTurnRightRadians( -3.05695 );
}
if ( target.energy != target.speed ) {
    setAhead( target.distance );
}
else if ( target.head != direction ) {
    setTurnRightRadians( 5.48603 );
}
else if ( target.energy > target.energy ) {
    setTurnRightRadians( -1.48643 );
}
	}
	public void onHitWall(HitWallEvent e) {
reverseDirection( -6.26448 );
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
