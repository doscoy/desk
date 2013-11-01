#ifndef MANDELBLOT_HPP_INCLUDED
#define MANDELBLOT_HPP_INCLUDED






class VdcMapper {
public:
    VdcMapper( const int width, const int height )
    : width_(width)
    , height_(height)
    , vc_max_y_(1.2f)
    , vc_x_(0)
    , vc_y_(0)
    {
    
        vc_y_ = -1 * vc_max_y_;
        vc_x_ = ((double)width_ * vc_y_) / (double)height_;
    }
    
    ~VdcMapper(){}
    
    
    void init( const int width, const int height ){
        width_ = width;
        height_ = height;
        vc_y_ = -1 * vc_max_y_;
        vc_x_ = ((double)width_ * vc_y_) / (double)height_;
    }
    
    void setMaxY(const double max_y){
        double diff = max_y - vc_max_y_;
        vc_max_y_ = max_y;
        vc_y_ -= diff;
        vc_x_ -= ((diff * (double)width_) / (double)height_);
    }

    unsigned int getDcWidth() const {
        return width_;
    }
    
    unsigned int getDcHeight() const {
        return height_;
    }
    
    void setCenterVcX( const float x ){
        vc_x_ = x - (getVcWidth() / 2.0f);
    }
    
    void setCenterVcY( const float y ){
        vc_y_ = y - (getVcHeight() / 2.0f);
    }
    
    double getCenterVcX() const {
        return (vc_x_ + (getVcWidth() / 2.0f));
    }
    
    double getCenterVcY() const {
        return (vc_y_ + (getVcHeight() / 2.0f));
    }
    
    void setCenterWithDcXY( const int x, const int y ){
        vc_x_ = vc_x_ + getVcX(x) - getVcX((unsigned int)(0.5f * ((double)width_ + 0.5f)));
        vc_y_ = vc_y_ + getVcY(y) - getVcY((unsigned int)(0.5f * ((double)height_ + 0.5f)));
    }
    
    
    double getStep() const {
        return (getVcHeight() / (double)height_ );
    }
    
    double getVcX0() const {
        return vc_x_;
    }
    
    double getVcY0() const {
        return vc_y_;
    }
    
    double getMaxY() const {
        return vc_max_y_;
    }

private:
    double getVcHeight() const {
        return (vc_max_y_ * 2.0f);
    }
    
    double getVcWidth() const {
        return (getVcHeight() * (double)width_ / (double)height_);
    }
    
    double getVcX( const int dc_x ) const {
        double x = ((getVcWidth() * (double)dc_x) / (double)width_) + vc_x_;
        return x;
    }
    
    double getVcY( const int dc_y ) const {
        double y = ((getVcHeight() * (double)dc_y) / (double)height_) + vc_y_;
        return y;
    }
    
    
    
private:
    int width_;
    int height_;
    double vc_max_y_;
    double vc_x_;
    double vc_y_;
    
    
    
};















class Mandelblot {
public:
    Mandelblot( const int width, const int height, const int max_calc );
    ~Mandelblot();
    
    void calculate();
    void calculateCL();
    
    int getCalcNum( const double x, const double y, const int max_calc_num );
    
    void setCenterWithDcXY( const int x, const int y ){
        mapper_.setCenterWithDcXY(x, y);
    }
    int getCalc0Num(
            const double x,
            const double y,
            const int max_calc_num
    )const;
    
    
    void initialize(
        const int width,
        const int height,
        const int max_calc
    );
    
    void setCenterVcX( const double x ){
        mapper_.setCenterVcX(x);
    }
    
    void setCenterVcY( const double y ){
        mapper_.setCenterVcY(y);
    }
    
    double getCenterVcX() const {
        return mapper_.getCenterVcX();
    }
    
    double getCenterVcY() const {
        return mapper_.getCenterVcY();
    }
    
    void setMaxY( const double maxy ){
        mapper_.setMaxY(maxy);
    }
    
    double getMaxY() const {
        return mapper_.getMaxY();
    }
    
    
    int* getData() {
        return data_;
    }
    
public:
    int width_;
    int height_;
    int pixel_count_;
    int max_calc_num_;
    int* data_;
    
    
    VdcMapper mapper_;
    
};




#endif // MANDELBLOT_HPP_INCLUDED