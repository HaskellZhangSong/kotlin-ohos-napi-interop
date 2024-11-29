import { hilog } from '@kit.PerformanceAnalysisKit';
import testNapi from 'libentry.so';

type Ptr = Object

class KNBridgeObject {
  private _ptr_native: Ptr;

  public constructor() {
    hilog.info(0x0000, 'testTag', 'Test NAPI 2 + 3 = %{public}s', "this is test");
    this._ptr_native = testNapi.ObjBridge_create();
    hilog.info(0x0000, 'testTag', 'Test NAPI 2 + 3 = %{public}s', "this is test");
  }

  public foo(x : string) : string {
    return testNapi.ObjBridge_foo(this._ptr_native, x);
  }
}


@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            hilog.info(0x0000, 'testTag', 'Test NAPI 2 + 3 = %{public}d', testNapi.add(2, 3))
            let a : KNBridgeObject = new KNBridgeObject()
            a.foo("hello")
            hilog.info(0x0000, 'testTag', 'Test NAPI 2 + 3 = %{public}d', a.foo("hello"));
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}

