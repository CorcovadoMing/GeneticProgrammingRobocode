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
if ( target.head < 6.64703 ) {
    fire( 8.53804 );
}
else if ( target.x == -7.15081 ) {
    fire( target.distance );
}
if ( target.energy == 1.09195 && target.speed != target.y ) {
    fire( target.bearing );
}
if ( target.bearing == target.distance || target.energy != -7.02008 ) {
    fire( target.distance );
}
else if ( target.x != target.x && target.speed != target.y ) {
    fire( -9.40863 );
}
else if ( target.energy > 6.89699 ) {
    fire( 1.84372 );
}
else if ( target.speed > -7.40282 ) {
    fire( -9.48998 );
}
	}

	void doMovement() {
setAhead( ( target.head * direction ) );
setTurnRightRadians( ( target.x + -4.85907 ) );
if ( target.distance != 6.03983 || target.distance == target.bearing ) {
    setTurnRightRadians( target.energy );
}
if ( target.y < 5.69928 && target.bearing != target.y ) {
    setTurnRightRadians( target.energy );
}
else if ( target.speed != target.head ) {
    setTurnRightRadians( direction );
}
if ( target.y < 8.57821 || direction < target.energy ) {
    setAhead( target.distance );
}
	}
	public void onHitWall(HitWallEvent e) {
setAhead( -5.58491 );
if ( target.x != target.y ) {
    reverseDirection( 5.69339 );
}
if ( target.head != 8.68797 ) {
    setTurnRightRadians( target.y );
}
if ( direction != target.head ) {
    setAhead( -3.35956 );
}
else if ( target.y > 1.09977 && target.y > 2.0234 ) {
    setTurnRightRadians( target.y );
}
if ( target.x > 2.01284 ) {
    reverseDirection( direction );
    setAhead( target.y );
    if ( target.y == 2.73386 && target.head > -2.88573 ) {
        reverseDirection( 4.27456 );
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
