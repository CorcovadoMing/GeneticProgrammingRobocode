## Rule

- heading - absolute angle in degrees with 0 facing up the screen, positive clockwise.
   0 <= heading < 360 .

- bearing - relative angle to some object from your robot's heading, positive clockwise.
   -180 < bearing <= 180 .

- All coordinates are expressed as (x,y). 

- All coordinates are positive. 

- The origin (0,0) is at the bottom left of the screen. 

- Positive x is right. 

- Positive y is up.


## Control Method

### MainFunction

- void    resume() 
   Immediately resumes the movement you stopped by stop(), if any.

- void   run() 
   The main method in every robot.

- void   scan() 
   Scans for other robots.

- void   stop() 
   Immediately stops all movement, and saves it for a call to resume().

- void   stop(boolean overwrite) 
   Immediately stops all movement, and saves it for a call to resume().

### Actions

- void	ahead(double distance) 
   Immediately moves your robot ahead (forward) by distance measured in pixels.
 
- void	back(double distance) 
   Immediately moves your robot backward by distance measured in pixels.

- void	doNothing() 
   Do nothing this turn, meaning that the robot will skip it's turn.

- void	fire(double power) 
   Immediately fires a bullet.

- Bullet	fireBullet(double power) 
   Immediately fires a bullet.

- void	turnGunLeft(double degrees) 
   Immediately turns the robot's gun to the left by degrees.

- void	turnGunRight(double degrees) 
   Immediately turns the robot's gun to the right by degrees.

- void	turnLeft(double degrees) 
   Immediately turns the robot's body to the left by degrees.

- void	turnRight(double degrees) 
   Immediately turns the robot's body to the right by degrees.

- void  turnRadarLeft(double degrees) 
   Immediately turns the robot's radar to the left by degrees.

- void  turnRadarRight(double degrees) 
   Immediately turns the robot's radar to the right by degrees.

***

- void   setAdjustGunForRobotTurn(boolean independent) 
   Sets the gun to turn independent from the robot's turn.

- void   setAdjustRadarForGunTurn(boolean independent) 
   Sets the radar to turn independent from the gun's turn.

- void   setAdjustRadarForRobotTurn(boolean independent) 
   Sets the radar to turn independent from the robot's turn.


### GetInformations

- double	getEnergy() 
   Returns the robot's current energy.

- double	getGunCoolingRate() 
   Returns the rate at which the gun will cool down, i.e. the amount of heat the gun heat will drop per turn.

- double	getGunHeading() 
   Returns the direction that the robot's gun is facing, in degrees.

- double	getGunHeat() 
   Returns the current heat of the gun.

- double	getHeading() 
   Returns the direction that the robot's body is facing, in degrees.

- double	getHeight() 
   Returns the height of the robot measured in pixels.

- double	getRadarHeading() 
   Returns the direction that the robot's radar is facing, in degrees.

- double	getVelocity() 
   Returns the velocity of the robot measured in pixels/turn.

- double	getWidth() 
   Returns the width of the robot measured in pixels.

- double	getX() 
   Returns the X position of the robot. (0,0) is at the bottom left of the battlefield.

- double	getY() 
   Returns the Y position of the robot. (0,0) is at the bottom left of the battlefield.

## Events

- void    onBattleEnded(BattleEndedEvent event) 
   This method is called after the end of the battle, even when the battle is aborted.

- void   onBulletHit(BulletHitEvent event) 
   This method is called when one of your bullets hits another robot.

- void   onBulletHitBullet(BulletHitBulletEvent event) 
   This method is called when one of your bullets hits another bullet.

- void   onBulletMissed(BulletMissedEvent event) 
   This method is called when one of your bullets misses, i.e. hits a wall.

- void   onDeath(DeathEvent event) 
   This method is called if your robot dies.

- void   onHitByBullet(HitByBulletEvent event) 
   This method is called when your robot is hit by a bullet.

- void   onHitRobot(HitRobotEvent event) 
   This method is called when your robot collides with another robot.

- void   onHitWall(HitWallEvent event) 
   This method is called when your robot collides with a wall.

- void   onRobotDeath(RobotDeathEvent event) 
   This method is called when another robot dies.

- void   onRoundEnded(RoundEndedEvent event) 
   This method is called after the end of a round.

- void   onScannedRobot(ScannedRobotEvent event) 
   This method is called when your robot sees another robot, i.e. when the robot's radar scan "hits" another robot.

- void   onStatus(StatusEvent e) 
   This method is called every turn in a battle round in order to provide the robot status as a complete snapshot of the robot's current state at that specific time.

- void   onWin(WinEvent event) 
   This method is called if your robot wins a battle.
