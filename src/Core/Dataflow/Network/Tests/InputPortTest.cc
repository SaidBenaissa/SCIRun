/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include <Core/Dataflow/Network/Port.h>
#include <Core/Dataflow/Network/Connection.h>
#include <Core/Dataflow/Network/Tests/MockModule.h>
#include <Core/Dataflow/Network/Tests/MockPorts.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>

using namespace SCIRun::Domain::Networks;
using namespace SCIRun::Domain::Networks::Mocks;
using namespace SCIRun::Domain::Datatypes;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::DefaultValue;

class InputPortTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    DefaultValue<InputPortHandle>::Set(InputPortHandle());
    DefaultValue<OutputPortHandle>::Set(OutputPortHandle());
    
    inputModule.reset(new NiceMock<MockModule>);
    outputModule.reset(new NiceMock<MockModule>);
  }

  MockModulePtr inputModule;
  MockModulePtr outputModule;
};


TEST_F(InputPortTest, GetValueBehavior)
{
  Port::ConstructionParams pcp("Matrix", "ForwardMatrix", "dodgerblue");

  MockDatatypeSinkPtr sink(new NiceMock<MockDatatypeSink>);

  InputPortHandle inputPort(new InputPort(inputModule.get(), pcp, sink));

  //no connection hooked up, so should exit before going to the sink.
  EXPECT_CALL(*sink, waitForData()).Times(0);
  EXPECT_CALL(*sink, receive()).Times(0);
  DatatypeHandleOption data = inputPort->get();
  EXPECT_FALSE(data);



  OutputPortHandle outputPort(new OutputPort(outputModule.get(), pcp, DatatypeSourceInterfaceHandle()));
  EXPECT_CALL(*inputModule, get_input_port(2)).WillOnce(Return(inputPort));
  EXPECT_CALL(*outputModule, get_output_port(1)).WillOnce(Return(outputPort));
  Connection c(outputModule, 1, inputModule, 2, "test");

  EXPECT_CALL(*sink, waitForData()).Times(1);
  EXPECT_CALL(*sink, receive()).Times(1);
  data = inputPort->get();
  EXPECT_TRUE(data);



  //ASSERT_EQ(0, inputPort->nconnections());
  //ASSERT_EQ(0, outputPort->nconnections());
  //{
  
  //  //connection added on construction
  //  ASSERT_EQ(1, inputPort->nconnections());
  //  ASSERT_EQ(1, outputPort->nconnections());
  //  ASSERT_EQ(&c, inputPort->connection(0));
  //  ASSERT_EQ(&c, outputPort->connection(0));
  //}
  ////and removed on destruction
  //ASSERT_EQ(0, inputPort->nconnections());
  //ASSERT_EQ(0, outputPort->nconnections());

  EXPECT_TRUE(false);
}