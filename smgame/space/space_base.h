#pragma once
namespace smgame {

	using LengthUnit = double;

	class Position {
	public:
		Position() :x(0), y(0), z(0) {}
		Position(LengthUnit x, LengthUnit y) :x(x), y(y), z(0) {}
		Position(LengthUnit x, LengthUnit y, LengthUnit z) :x(x), y(y), z(z) {}
	public:
		LengthUnit x, y, z;
	};

	using Point = Position;

	template<typename Type>
	inline bool Impact(const Type& o, const Point& p) { return o.Impact(o); }
	template<typename Type>
	inline bool Impact(const Point& p, const Type& o) { return o.Impact(o); }

	class Line {
	public:
		Position start, end;
	};
	namespace x2d {
		enum class CoordinateLineType
		{
			ParrallelX,
			ParrallelY,
		};

		//CoordinateLine A line parallel to the coordinate axis.
		class CoordinateLine {
		public:
			CoordinateLineType Type;
			LengthUnit Pos, Start, End;
		public:
			Point startPoint() const;
			Point endPoint() const;
		};

		template<typename Type>
		inline bool Impact(const Type& o, const CoordinateLine& p) { return o.Impact(o); }
		template<typename Type>
		inline bool Impact(const CoordinateLine& p, const Type& o) { return o.Impact(o); }
	}

	namespace x3d {
		enum class CoordinateLineType
		{
			ParrallelX,
			ParrallelY,
			ParrallelZ,
		};

		//CoordinateLine A line parallel to the coordinate axis.
		class CoordinateLine {
		public:
			CoordinateLineType Type;
			Point Pos;
			LengthUnit Start, End;

		public:
		};
	}

	LengthUnit distance(Point a, Point b);
}