class TrafficLight {
    mutex m;
    int cnt = 0;
    int currRoadId;
public:
    TrafficLight() {
        currRoadId = 1;
    }

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        lock_guard<mutex> ul(m);
        if(currRoadId!=roadId){
            turnGreen();
            currRoadId = roadId;
        }
        crossCar();
        
    }
};