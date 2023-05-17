#include <DGtal/helpers/StdDefs.h>

#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"

#include <DGtal/topology/DigitalSurface.h>
#include <DGtal/topology/DigitalSetBoundary.h>
#include <DGtal/topology/CanonicCellEmbedder.h>
#include <DGtal/topology/CanonicSCellEmbedder.h>

#include <DGtal/shapes/Shapes.h>

#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/colormaps/GradientColorMap.h>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/errors.hpp>

#include <stack>
#include <fstream>

enum SHAPE_TYPE
{
  BALL,
  FLOWER,
  ACC_FLOWER
};

std::istream& operator>>( std::istream& is, SHAPE_TYPE& shape_type )
{
  namespace po = boost::program_options;

  std::string token;
  is >> token;
  if( token == "ball" ) { shape_type = BALL; return is; }
  if( token == "flower" ) { shape_type = FLOWER; return is; }
  if( token == "accFlower" ) { shape_type = ACC_FLOWER; return is; }

  throw po::validation_error( po::validation_error::invalid_option_value );
  return is;
}

std::ostream& operator<<( std::ostream& os, SHAPE_TYPE& shape_type )
{
  switch( shape_type )
  {
    case BALL:
      os << "ball";
      break;
    case FLOWER:
      os << "flower";
      break;
    case ACC_FLOWER:
      os << "accFlower";
      break;
  }

  return os;
}

struct Options
{
  SHAPE_TYPE shape_type;
  double h;
  bool contour_points;
  bool board;
};

Options parse_options(int argc, char* argv[])
{
  namespace po = boost::program_options;

  using DGtal::trace;
  using std::endl;

  Options options;

  po::options_description po_options("contour extraction [options]");
  po_options.add_options()
    ("shape-type,t", po::value<SHAPE_TYPE>(&options.shape_type)->default_value(BALL), "ball, flower or accFlower")
    ("grid-step,s", po::value<double>(&options.h)->default_value(0.1), "grid step")
    ("contour-points,c", po::value<bool>(&options.contour_points)->default_value(true), "true: only contour points, false: all points")
    ("board,b", po::value<bool>(&options.board)->default_value(true), "true: draw board, false: don't draw")

    ("help,h", "display this message")
    ;

  try
  {
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(po_options).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
      trace.info() << po_options;
      std::exit(0);
    }
  }
  catch (std::exception& ex)
  {
    trace.error() << ex.what() << endl;
    trace.info() << po_options;
    std::exit(1);
  }

  return options;
}

template <typename TShape>
void generate_points( Options& options, TShape shape, DGtal::Board2D& board, std::vector<DGtal::Z2i::Space::Point>& v )
{
  using namespace DGtal;

  typedef Z2i::Space Space;
  typedef Space::RealVector RealVector;
  typedef Space::Point Point;
  typedef Space::RealPoint RealPoint;
  typedef GaussDigitizer<Space, TShape> Digitizer;
  typedef typename Digitizer::Domain Domain;
  typedef KhalimskySpaceND<Space::dimension, int> KSpace;
  typedef KSpace::SCell SCell;
  typedef KSpace::Cell Cell;
  typedef SurfelAdjacency<Space::dimension> SurfelAdjacency;

  trace.beginBlock("Extracting Contour Points");

  trace.info() << "h=" << options.h << std::endl;

  Digitizer digitizer;
  digitizer.attach( shape );
  digitizer.init( shape.getLowerBound() + RealVector(-1,-1), shape.getUpperBound() + RealVector(1,1), options.h );

  Domain domain = digitizer.getDomain();
  if(options.board) board << domain;


  if( options.contour_points )
  {
    KSpace kspace;
    bool ok = kspace.init(domain.lowerBound(), domain.upperBound(), true);
    if( !ok ) trace.error() << "KSpace init failed" << std::endl;

    SurfelAdjacency SAdj(true);
    typename KSpace::Surfel bel = Surfaces<KSpace>::findABel(kspace, digitizer, 100000);

    typedef CanonicSCellEmbedder<KSpace> CanonicSCellEmbedder;
    CanonicSCellEmbedder canonicSCellEmbedder( kspace );

    std::vector<SCell> sCells1;
    Surfaces<KSpace>::track2DBoundary(sCells1, kspace, SAdj, digitizer, bel);

    for( int i = 0; i < sCells1.size(); i++ )
    {
      const auto sCells = kspace.sUpperIncident( sCells1[i] );
      for( auto const& s : sCells )
        if( digitizer( digitizer.round( options.h * canonicSCellEmbedder( s ) ) ) )
        {
          v.push_back(digitizer.round(options.h * canonicSCellEmbedder(s)));
        }
    }
  }
  else
  {
    for( auto const& p : domain )
      if( digitizer( p ) ) 
        v.push_back( p );
  }

  std::sort(v.begin(), v.end());
  auto last = std::unique(v.begin(), v.end());
  v.erase(last, v.end()); 

  trace.endBlock();
}

int main( int argc, char** argv )
{
  Options options = parse_options( argc, argv );

  using namespace DGtal;

  typedef Z2i::Space::Point Point;

  trace.beginBlock("Convex Hull");

  std::vector<Point> points;
  DGtal::Board2D board;

  if( options.shape_type == BALL ) generate_points( options,
      DGtal::Ball2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1. ), board,
      points );
  if( options.shape_type == FLOWER ) generate_points( options,
      DGtal::Flower2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1., 0.3, 5, 0. ),board,
      points );
  if( options.shape_type == ACC_FLOWER ) generate_points( options,
      DGtal::AccFlower2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1., 0.3, 5, 0. ),board,
      points );

  if(options.board)     for (const auto& p : points) board << p ;

  trace.info() << "Extracted " << points.size() << " points." << std::endl;

  const auto compare_points = [] ( const Point& a, const Point& b ) -> bool
  {
    if( a[1] != b[1] ) return a[1] < b[1];
    else return a[0] < b[0];
  };

  Point pivot;

  const auto ccw = [] (const Point& a, const Point& b, const Point& c) -> int
  {
    int area = (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]);
    if (area > 0)
      return -1;
    else if (area < 0)
      return 1;
    return 0;
  };

  const auto polar_order = [&](const Point& a, const Point& b)
  {
    int order = ccw(pivot, a, b);
    if (order == 0)
      return (pivot - a).norm() < (pivot - b).norm();
    return (order == -1);
  };

  const auto graham = [&](std::vector<Point>& points)
  {
    trace.beginBlock("Graham");
    const int N = points.size();

    trace.info() << "Graham on " << N << " points." << std::endl;
    std::stack<Point> hull;

    if (N < 3)
      return hull;

    // find the point having the least y coordinate (pivot),
    // ties are broken in favor of lower x coordinate
    trace.beginBlock("Finding the lowest point");
    auto min_it = std::min_element(points.cbegin(), points.cend(), compare_points);
    trace.endBlock();

    // swap the pivot with the first point
    std::swap(points[0], points[std::distance(points.cbegin(), min_it)]);

    // sort the remaining point according to polar order about the pivot
    pivot = points[0];
    trace.beginBlock("Sorting using polar order");
    std::sort(points.begin() + 1, points.end(), polar_order);
    trace.endBlock();

    if(options.board)
      for (int i = 0; i < N; ++i)
      {
        board << CustomStyle( points[i].className(), new CustomFillColor( Color(i*255/N,i*255/N,i*255/N) ) ) << points[i] ;
      }

    trace.beginBlock("Computing the hull");

    hull.push(points[0]);
    hull.push(points[1]);

    for (int i = 2; i < N; i++)
    {
      Point top = hull.top();
      hull.pop();
      while (  hull.size() >= 1 && ccw( hull.top(), top, points[i] ) != -1)
      {
        top = hull.top();
        hull.pop();
      }
      hull.push( top );
      hull.push( points[i] );
    }
    trace.endBlock();

    trace.endBlock();

    return hull;
  };

  std::stack<Point> hull = graham( points );

  trace.emphase() << "Points in hull : " << hull.size() << std::endl;

  if(hull.size() > 0)
  {
    Point tmp_point = hull.top();
    Point first = tmp_point;
    hull.pop();
    if(options.board) board << CustomStyle( tmp_point.className(), new CustomFillColor( Color(255,0, 0) ) ) << first ;

    while (! hull.empty() )
    {
      Point p = hull.top();
      if(options.board) board << CustomStyle( p.className(), new CustomFillColor( Color(255,0, 0) ) ) << p ;
      if(options.board) board.drawLine(tmp_point[0], tmp_point[1], p[0], p[1]);
      tmp_point = p;
      hull.pop();
    }
    if(options.board)  board.drawLine(tmp_point[0], tmp_point[1], first[0], first[1]);
  }

  if(options.board) board.saveSVG ( "hull.svg" );

  trace.endBlock();
}
