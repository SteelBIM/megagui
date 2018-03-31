extern "C"{
#pragma pack(2)
	struct DistributedLoads{
		int dis_x1;
		int dis_x2;
		float load_q1;
		float load_q2;
	};

	struct Concentratedloads{
		int dis_x;
		float load_f;
	};

	struct EndLoads{
		float load_axialN;
		float load_bottomM;
		float load_topM;
	};
};