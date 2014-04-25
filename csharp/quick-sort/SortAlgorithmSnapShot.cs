using System.Collections;

namespace SortAlgorithm
{
    public class SortAlgorithmSnapShot: ISortAlgorithmSnapShot
    {
        public double[] Data { get; private set; }
        public Hashtable Pointers { get; private set; }

        public SortAlgorithmSnapShot(ISortAlgorithm sort)
        {
            Initial();

            sort.SetSnapShot(this);
        }

        public void SetData(double[] data)
        {
            Data = new double[data.Length];
            data.CopyTo(Data, 0);
        }
        
        public void SetPointer(string name, int index)
        {
            Pointers[name] = index;
        }

        private void Initial()
        {
            Pointers = new Hashtable();
        }
    }
}
