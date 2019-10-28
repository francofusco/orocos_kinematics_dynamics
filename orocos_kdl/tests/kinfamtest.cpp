#include "kinfamtest.hpp"
#include <frames_io.hpp>
#include <kinfam_io.hpp>
#include <chainfksolverpos_recursive.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION( KinFamTest );

#ifdef  __APPLE__
typedef unsigned int uint;
#endif

using namespace KDL;
using namespace std;

void KinFamTest::setUp()
{
}

void  KinFamTest::tearDown()
{
}

void KinFamTest::JointTest()
{
    double q;
    Joint j;
    j=Joint("Joint 1", Joint::None);
    CPPUNIT_ASSERT_EQUAL(Joint::None,j.getType());
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.pose(q),Frame::Identity());
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.twist(q),Twist::Zero());
    random(q);
    j=Joint("Joint 2", Joint::RotX);
    CPPUNIT_ASSERT_EQUAL(Joint::RotX,j.getType());
    CPPUNIT_ASSERT_EQUAL(j.pose(q),Frame(Rotation::RotX(q)));
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.twist(q),Twist(Vector::Zero(),Vector(q,0,0)));
    random(q);
    j=Joint("Joint 3", Joint::RotY);
    CPPUNIT_ASSERT_EQUAL(Joint::RotY,j.getType());
    CPPUNIT_ASSERT_EQUAL(j.pose(q),Frame(Rotation::RotY(q)));
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.twist(q),Twist(Vector::Zero(),Vector(0,q,0)));
    random(q);
    j=Joint("Joint 4", Joint::RotZ);
    CPPUNIT_ASSERT_EQUAL(Joint::RotZ,j.getType());
    CPPUNIT_ASSERT_EQUAL(j.pose(q),Frame(Rotation::RotZ(q)));
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.twist(q),Twist(Vector::Zero(),Vector(0,0,q)));
    random(q);
    j=Joint("Joint 5", Joint::TransX);
    CPPUNIT_ASSERT_EQUAL(Joint::TransX,j.getType());
    CPPUNIT_ASSERT_EQUAL(j.pose(q),Frame(Vector(q,0,0)));
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.twist(q),Twist(Vector(q,0,0),Vector::Zero()));
    random(q);
    j=Joint("Joint 6", Joint::TransY);
    CPPUNIT_ASSERT_EQUAL(Joint::TransY,j.getType());
    CPPUNIT_ASSERT_EQUAL(j.pose(q),Frame(Vector(0,q,0)));
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.twist(q),Twist(Vector(0,q,0),Vector::Zero()));
    random(q);
    j=Joint("Joint 7", Joint::TransZ);
    CPPUNIT_ASSERT_EQUAL(Joint::TransZ,j.getType());
    CPPUNIT_ASSERT_EQUAL(j.pose(q),Frame(Vector(0,0,q)));
    random(q);
    CPPUNIT_ASSERT_EQUAL(j.twist(q),Twist(Vector(0,0,q),Vector::Zero()));

}

void KinFamTest::SegmentTest()
{
    Segment s;
    double q,qdot;
    Frame f,f1;
    random(f);
    s = Segment("Segment 0", Joint("Joint 0", Joint::None),f);
    random(q);
    random(qdot);
    f1=s.getJoint().pose(q)*f;
    CPPUNIT_ASSERT_EQUAL(f1,s.pose(q));
    CPPUNIT_ASSERT_EQUAL(s.getJoint().twist(qdot).RefPoint(f1.p),s.twist(q,qdot));
    random(f);
    s = Segment("Segment 1", Joint("Joint 1", Joint::RotX),f);
    random(q);
    random(qdot);
    f1=s.getJoint().pose(q)*f;
    CPPUNIT_ASSERT_EQUAL(f1,s.pose(q));
    CPPUNIT_ASSERT_EQUAL(s.getJoint().twist(qdot).RefPoint(f1.p),s.twist(q,qdot));
    random(f);
    s = Segment("Segment 3", Joint("Joint 3", Joint::RotY),f);
    random(q);
    random(qdot);
    f1=s.getJoint().pose(q)*f;
    CPPUNIT_ASSERT_EQUAL(f1,s.pose(q));
    CPPUNIT_ASSERT_EQUAL(s.getJoint().twist(qdot).RefPoint(f1.p),s.twist(q,qdot));
    random(f);
    s = Segment("Segment 4", Joint("Joint 4", Joint::RotZ),f);
    random(q);
    random(qdot);
    f1=s.getJoint().pose(q)*f;
    CPPUNIT_ASSERT_EQUAL(f1,s.pose(q));
    CPPUNIT_ASSERT_EQUAL(s.getJoint().twist(qdot).RefPoint(f1.p),s.twist(q,qdot));
    random(f);
    s = Segment("Segment 5", Joint("Joint 5", Joint::TransX),f);
    random(q);
    random(qdot);
    f1=s.getJoint().pose(q)*f;
    CPPUNIT_ASSERT_EQUAL(f1,s.pose(q));
    CPPUNIT_ASSERT_EQUAL(s.getJoint().twist(qdot).RefPoint(f1.p),s.twist(q,qdot));
    random(f);
    s = Segment("Segment 6", Joint("Joint 6", Joint::TransY),f);
    random(q);
    random(qdot);
    f1=s.getJoint().pose(q)*f;
    CPPUNIT_ASSERT_EQUAL(f1,s.pose(q));
    CPPUNIT_ASSERT_EQUAL(s.getJoint().twist(qdot).RefPoint(f1.p),s.twist(q,qdot));
    random(f);
    s = Segment("Segment 7", Joint("Joint 7", Joint::TransZ),f);
    random(q);
    random(qdot);
    f1=s.getJoint().pose(q)*f;
    CPPUNIT_ASSERT_EQUAL(f1,s.pose(q));
    CPPUNIT_ASSERT_EQUAL(s.getJoint().twist(qdot).RefPoint(f1.p),s.twist(q,qdot));
}

void KinFamTest::ChainTest()
{
    Chain chain1;

    chain1.addSegment(Segment("Segment 0", Joint("Joint 0", Joint::RotZ),
                              Frame(Vector(0.0,0.0,0.0))));
    chain1.addSegment(Segment("Segment 1", Joint("Joint 1", Joint::RotX),
                              Frame(Vector(0.0,0.0,0.9))));
    chain1.addSegment(Segment("Segment 2", Joint("Joint 2", Joint::RotX),
                              Frame(Vector(0.0,0.0,1.2))));
    chain1.addSegment(Segment("Segment 3", Joint("Joint 3", Joint::RotZ),
                              Frame(Vector(0.0,0.0,1.5))));
    chain1.addSegment(Segment("Segment 4", Joint("Joint 4", Joint::RotX),
                              Frame(Vector(0.0,0.0,0.0))));
    chain1.addSegment(Segment("Segment 5", Joint("Joint 5", Joint::RotZ),
                              Frame(Vector(0.0,0.0,0.4))));
    CPPUNIT_ASSERT_EQUAL(chain1.getNrOfJoints(),(uint)6);
    CPPUNIT_ASSERT_EQUAL(chain1.getNrOfSegments(),(uint)6);
    chain1.addSegment(Segment("Segment 6", Joint("Joint 6", Joint::None),Frame(Vector(0.0,0.1,0.0))));
    CPPUNIT_ASSERT_EQUAL(chain1.getNrOfJoints(),(uint)6);
    CPPUNIT_ASSERT_EQUAL(chain1.getNrOfSegments(),(uint)7);

    Chain chain2 = chain1;
    CPPUNIT_ASSERT_EQUAL(chain2.getNrOfJoints(),chain1.getNrOfJoints());
    CPPUNIT_ASSERT_EQUAL(chain2.getNrOfSegments(),chain1.getNrOfSegments());
    chain2.addChain(chain1);
    CPPUNIT_ASSERT_EQUAL(chain2.getNrOfJoints(),chain1.getNrOfJoints()*(uint)2);
    CPPUNIT_ASSERT_EQUAL(chain2.getNrOfSegments(),chain1.getNrOfSegments()*(uint)2);
    
    // test segment removal from chains
    Chain chain3(chain1);
    // try to remove an inexistent segment
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("Non existent segment"), (uint)0);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfJoints(), chain1.getNrOfJoints());
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfSegments(), chain1.getNrOfSegments());
    // try to from an invalid index
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom(chain3.getNrOfSegments()), (uint)0);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfJoints(), chain1.getNrOfJoints());
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfSegments(), chain1.getNrOfSegments());
    // remove the last segment (which is attached to a fixed joint)
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom(chain3.getNrOfSegments()-1), (uint)1);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfJoints(), chain1.getNrOfJoints());
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfSegments(), chain1.getNrOfSegments()-1);
    // reset the chain, then try to remove all segments/joints
    chain3 = chain1;
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom(0), chain1.getNrOfSegments());
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfJoints(), (uint)0);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfSegments(), (uint)0);
    CPPUNIT_ASSERT(chain3.segments.empty());
    // reset the chain, then try to remove the last 3 segments (having 2 moving joints)
    chain3 = chain1;
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("Segment 4"), (uint)3);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfJoints(), chain1.getNrOfJoints()-2);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfSegments(), chain1.getNrOfSegments()-3);
    CPPUNIT_ASSERT_EQUAL((uint)chain3.segments.size(), chain3.getNrOfSegments());
    // create a new chain with some segment names whith repetitions
    Chain chain4(chain1);
    chain4.addSegment(Segment("SegmentX", Joint("JointX", Joint::None)));
    chain4.addSegment(Segment("SegmentY", Joint("JointY", Joint::None)));
    chain4.addSegment(Segment("SegmentY", Joint("JointY", Joint::None)));
    chain4.addSegment(Segment("SegmentZ", Joint("JointZ", Joint::None)));
    chain4.addSegment(Segment("SegmentX", Joint("JointX", Joint::None)));
    chain4.addSegment(Segment("SegmentY", Joint("JointY", Joint::None)));
    CPPUNIT_ASSERT_EQUAL(chain4.getNrOfSegments(), chain1.getNrOfSegments()+6);
    CPPUNIT_ASSERT_EQUAL(chain4.getNrOfJoints(), chain1.getNrOfJoints());
    chain3 = chain4;
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("SegmentY"), (uint)1);
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("SegmentX"), (uint)1);
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("SegmentY"), (uint)2);
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("SegmentY"), (uint)1);
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("SegmentX"), (uint)1);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfJoints(), chain4.getNrOfJoints());
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfSegments(), chain4.getNrOfSegments()-6);
    // reset the chain, then remove similarly to before
    chain3  = chain4;
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("SegmentX"), (uint)2);
    CPPUNIT_ASSERT_EQUAL(chain3.deleteSegmentsFrom("SegmentX"), (uint)4);
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfJoints(), chain4.getNrOfJoints());
    CPPUNIT_ASSERT_EQUAL(chain3.getNrOfSegments(), chain4.getNrOfSegments()-6);
}

void KinFamTest::TreeTest()
{
    Tree tree1;
    Segment segment1("Segment 1", Joint("Joint 1", Joint::None));
    Segment segment2("Segment 2", Joint("Joint 2", Joint::RotX),Frame(Vector(0.1,0.2,0.3)));
    Segment segment3("Segment 3", Joint("Joint 3", Joint::TransZ),Frame(Rotation::RotX(1.57)));
    Segment segment4("Segment 4", Joint("Joint 4", Joint::RotX),Frame(Vector(0.1,0.2,0.3)));
    Segment segment5("Segment 5", Joint("Joint 5", Joint::RotX),Frame(Vector(0.1,0.2,0.3)));
    Segment segment6("Segment 6", Joint("Joint 6", Joint::RotX),Frame(Vector(0.1,0.2,0.3)));
    Segment segment7("Segment 7", Joint("Joint 7", Joint::RotX),Frame(Vector(0.1,0.2,0.3)));

    cout<<tree1<<endl;

    CPPUNIT_ASSERT(tree1.addSegment(segment1,"root"));
    CPPUNIT_ASSERT(tree1.addSegment(segment2,"root"));
    CPPUNIT_ASSERT(tree1.addSegment(segment3,"Segment 1"));
    CPPUNIT_ASSERT(tree1.addSegment(segment4,"Segment 3"));
    CPPUNIT_ASSERT(!tree1.addSegment(segment1,"Segment 6"));
    CPPUNIT_ASSERT(!tree1.addSegment(segment1,"Segment 4"));

    cout<<tree1<<endl;

    Tree tree2;
    CPPUNIT_ASSERT(tree2.addSegment(segment5,"root"));
    CPPUNIT_ASSERT(tree2.addSegment(segment6,"root"));
    CPPUNIT_ASSERT(tree2.addSegment(segment7,"Segment 6"));

    cout<<tree2<<endl;

    Chain chain1;
    chain1.addSegment(Segment("Segment 8", Joint("Joint 8", Joint::RotZ),
                              Frame(Vector(0.0,0.0,0.0))));
    chain1.addSegment(Segment("Segment 9", Joint("Joint 9", Joint::RotX),
                              Frame(Vector(0.0,0.0,0.9))));
    chain1.addSegment(Segment("Segment 10", Joint("Joint 10", Joint::RotX),
                              Frame(Vector(0.0,0.0,1.2))));
    chain1.addSegment(Segment("Segment 11", Joint("Joint 11", Joint::RotZ),
                              Frame(Vector(0.0,0.0,1.5))));
    chain1.addSegment(Segment("Segment 12", Joint("Joint 12", Joint::RotX),
                              Frame(Vector(0.0,0.0,0.0))));
    chain1.addSegment(Segment("Segment 13", Joint("Joint 13", Joint::RotZ),
                              Frame(Vector(0.0,0.0,0.4))));


    CPPUNIT_ASSERT(tree2.addChain(chain1, "Segment 6"));
    cout<<tree2<<endl;
    CPPUNIT_ASSERT(tree1.addTree(tree2, "Segment 2"));
    cout<<tree1<<endl;

    Chain extract_chain1;
    CPPUNIT_ASSERT(tree1.getChain("Segment 2", "Segment 4", extract_chain1));
    Chain extract_chain2; 
    CPPUNIT_ASSERT(tree1.getChain("Segment 4", "Segment 2", extract_chain2));
    CPPUNIT_ASSERT(tree1.getChain("Segment 4", "Segment 2", extract_chain2));
    CPPUNIT_ASSERT(extract_chain1.getNrOfJoints()==extract_chain2.getNrOfJoints());
    CPPUNIT_ASSERT(extract_chain1.getNrOfSegments()==extract_chain2.getNrOfSegments());
    ChainFkSolverPos_recursive solver1(extract_chain1);
    ChainFkSolverPos_recursive solver2(extract_chain2);


    Frame f1, f2;
    JntArray jnt1(extract_chain2.getNrOfJoints());
    JntArray jnt2(extract_chain2.getNrOfJoints());
    for (int i=0; i<(int)extract_chain2.getNrOfJoints(); i++){
      jnt1(i) = (i+1)*2;
      jnt2((int)extract_chain2.getNrOfJoints()-i-1) = jnt1(i);
    }
    solver1.JntToCart(jnt1, f1);
    solver2.JntToCart(jnt2, f2);
    CPPUNIT_ASSERT(f1 == f2.Inverse());
}



